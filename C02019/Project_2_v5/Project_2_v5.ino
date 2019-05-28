/*
 * Reference :
 * +  lib RFRC 522
 * +  lib DHT11
 * +  some source code from internet
 * Modify : LQT
 * +  project_version_3 source code
 */

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ticker.h>
#include "DHT.h"

#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices

#include <SoftwareSerial.h>

const int button = 4; // D2

#define DHTPIN D3
#define DHTTYPE DHT11

#define analogPin A0
int buttonVal; // store value from the analog pin
int button_D2; // store value of button D2

#define sda_pin D9 // D9 : rx
#define scl_pin D10 // D10 : tx

#define RST_PIN D4          // Configurable, see typical pin layout above
#define SS_PIN  D8          // Configurable, see typical pin layout above

#define RX  D0
#define TX  D1

// SERVER
#define FIREBASE_HOST ***************
#define FIREBASE_AUTH "***************

// AP
#define WIFI_SSID ***************
#define WIFI_PASSWORD "***************

// Phone number
String SDT = *************;
float t; //temperaute
float h; //humidity

int button_1;
int button_2;
int button_3;

SoftwareSerial sim808(TX, RX);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(TX, RX);

//for LCD                1                2               3             4             5             6               7          8
String menuItems[] = {"TEM AND HUM", "UPLOAD DATA", "SENDING SMS", "INSERT CARD", "DELETE CARD", /*"CHECK MODULE", "SETTING",*/ "LOG OUT"};
int menuPage = 0;
//int maxMenuPages = round(((sizeof(menuItems) / sizeof(String)) / 2) + .5);
int maxMenuPages = 4;
//                             1               2                 3           6               7         8
String menuClientItems[] = {"TEM AND HUM", "UPLOAD DATA", "SENDING SMS", /*"CHECK MODULE", "SETTING",*/ "LOG OUT"};
int menuClientPage = 0;
int maxMenuClientPages = round(((sizeof(menuClientItems) / sizeof(String)) / 2) + .5);


int cursorPosition = 0;


byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

void setup_LCD();
void setup_DHT();
void setup_button();
void setup_800L();
void setup_ESP8266();
void setup_firebase();

void read_DHT();
void LCD_display();
void send_message();
void updateSerial();
void updateData();
bool check_master_RC522();

bool check_client_RC522();
void clientMenuDraw();
void operateClientMenu();
void drawClientCursor();

void read_Button();

void drawCursor();
void operateMainMenu();
void mainMenuDraw();
int evaluateButton(int x);


void menuItem1();
void menuItem2();
void menuItem3();
void menuItem4();
void menuItem5();

void at(String _atcm, unsigned long _dl);

void setup() {
  setup_8266();
  delay(100);
  setup_firebase();
  delay(100);
  setup_800L();
  delay(100);
  setup_button();
  delay(100);
  setup_LCD();
  delay(100);
  setup_DHT();
  delay(100);
  setup_RC522();
  delay(100);

}

int my_restart = 0;
String master_id = ""; // not yet
String id = ""; // not yet
int change_menu_1 = 1;
int changeMenu = 1;


int time_flag_1 = 0;
int time_counter_1 = 0;

void set_time_1(int value) {
  time_counter_1 = value;
  time_flag_1 = 0;
}

void time_click_1() {
  if (time_counter_1 > 0) {
    time_counter_1--;
    if (time_counter_1 == 0)
      time_flag_1 = 1;
  }
}

void loop() {
  int button = 0;
  read_Button();
  button = evaluateButton();
  button_1 = 0;
  button_2 = 0;
  button_3 = 0;

  if (button == 2) {
    lcd.setCursor(1, 0);
    lcd.clear();
    lcd.print("PUT MASTER CARD");
    set_time_1(100);
    while (time_flag_1 == 0) {
      ESP.wdtDisable();
      if (check_master_RC522() == true ) {
        while (1) {
          if (changeMenu == 1) {
            ESP.wdtDisable();
            mainMenuDraw();
            drawCursor();
            changeMenu = 0;
          }
          operateMenu();

          if (my_restart == 1) {
            my_restart = 0;
            menuPage = 0;
            cursorPosition = 0;
            changeMenu = 1;
            break;
          }
          delay(120);
        }
      }

      time_click_1();
      delay(50);
    }
    change_menu_1 = 1;
  }
  else if (button == 3) {
    ESP.wdtDisable();
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("PUT CLIENT CARD");
    set_time_1(100);
    while (time_flag_1 == 0) {
      ESP.wdtDisable();
      if (check_client_RC522() == true ) {
        while (1) {
          ESP.wdtDisable();
          if (changeMenu == 1) {
            mainMenuClientDraw();
            drawClientCursor();
            changeMenu = 0;
          }
          operateClientMenu();

          if (my_restart == 1) {
            my_restart = 0;
            menuClientPage = 0;
            cursorPosition = 0;
            changeMenu = 1;
            break;
          }
          delay(120);
        }
      }
      time_click_1();
      delay(50);
    }
    change_menu_1 = 1;
  }
  else {
    if (change_menu_1 == 1) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("MASTER CARD");
      lcd.setCursor(1, 1);
      lcd.print("CLIENT CARD");
      change_menu_1 = 0;
    }
  }
  ESP.wdtDisable();
  delay(120);
}

void setup_firebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void setup_8266() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void setup_800L() {
  sim808.begin(9600);
}

void setup_button() {
  pinMode(button, INPUT);
  pinMode(analogPin, INPUT);
  delay(100);
}

void setup_RC522() {
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                           // Init MFRC522 card
}

void setup_DHT() {
  dht.begin();
}

void setup_LCD() {
  Wire.begin(sda_pin, scl_pin); // Wire.begin(SDA, SCL)
  delay(200);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("0000000000000000");
  delay(100);
  int i;
  for (i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.print('0');
    delay(100);
  }
  lcd.clear();
  lcd.createChar(0, menuCursor);
}

void drawCursor() {
  for (int x = 0; x < 2; x++) {
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  if (menuPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

void drawClientCursor() {
  for (int x = 0; x < 2; x++) {
    lcd.setCursor(0, x);
    lcd.print(" ");
  }

  if (menuClientPage % 2 == 0) {
    if (cursorPosition % 2 == 0) {
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
  }
  if (menuClientPage % 2 != 0) {
    if (cursorPosition % 2 == 0) {
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
    }
    if (cursorPosition % 2 != 0) {
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
    }
  }
}

int evaluateButton() {
  int result = 0;
  if (button_1 == 1) {
    result = 3; // down
  } else if ( button_2 == 1) {
    result = 2; // up
  } else if ( button_3 == 1) {
    result = 1; // enter
  }
  return result;
}

void mainMenuDraw() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuItems[menuPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuItems[menuPage + 1]);
}

void mainMenuClientDraw() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print(menuClientItems[menuClientPage]);
  lcd.setCursor(1, 1);
  lcd.print(menuClientItems[menuClientPage + 1]);
}

void read_Button() {
  buttonVal = analogRead(analogPin);

  if (buttonVal > 0) {
    if ( buttonVal >= 870 && buttonVal <= 900)
      button_1 = 1;
    else if ( buttonVal >= 750 && buttonVal <= 830 )
      button_2 = 1;
    else if ( buttonVal >= 910 && buttonVal <= 1000 )
      button_3 = 1;
  }

}

void operateMenu() {
  int activeButton = 0;
  ESP.wdtDisable();
  if (activeButton == 0) {
    int button;
    read_Button();
    button = evaluateButton();
    button_1 = 0;
    button_2 = 0;
    button_3 = 0;
    switch (button) {
      case 0:
        break;
      case 1:
        button = 0;
        switch (cursorPosition) {
          case 0:
            menuItem1();
            break;
          case 1:
            menuItem2();
            break;
          case 2:
            menuItem3();
            break;
          case 3:
            menuItem4();
            break;
          case 4:
            menuItem5();
            break;/*
          case 5:
            menuItem6();
            break;
          case 6:
            menuItem7();
            break; */
          case 5:
            menuItem8();
          default:
            break;
        }

        activeButton = 1;
        changeMenu = 1;

        break;
      case 2:
        button = 0;
        if (menuPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));
        }
        if (menuPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage - 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

        activeButton = 1;
        changeMenu = 1;

        break;
      case 3:
        button = 0;
        if (menuPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }

        if (menuPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuPage = menuPage + 1;
          menuPage = constrain(menuPage, 0, maxMenuPages);
        }
        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuItems) / sizeof(String)) - 1));

        activeButton = 1;
        changeMenu = 1;
        break;
      default:
        break;
    }
  }
}


void operateClientMenu() {
  int activeButton = 0;
  ESP.wdtDisable();
  if (activeButton == 0) {
    int button;
    read_Button();
    button = evaluateButton();
    button_1 = 0;
    button_2 = 0;
    button_3 = 0;
    switch (button) {
      case 0:
        break;
      case 1:
        button = 0;
        switch (cursorPosition) {
          case 0:
            menuItem1();
            break;
          case 1:
            menuItem2();
            break;
          case 2:
            menuItem3();
            break;
          /*case 3:
            menuItem4();
            break;
          case 4:
            menuItem5();
            break; */
          case 3:
            menuItem8(); // log out
            break;
          default:
            break;
        }

        activeButton = 1;
        changeMenu = 1;

        break;
      case 2:
        button = 0;
        if (menuClientPage == 0) {
          cursorPosition = cursorPosition - 1;
          cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuClientItems) / sizeof(String)) - 1));
        }
        if (menuClientPage % 2 == 0 and cursorPosition % 2 == 0) {
          menuClientPage = menuClientPage - 1;
          menuClientPage = constrain(menuClientPage, 0, maxMenuPages);
        }

        if (menuClientPage % 2 != 0 and cursorPosition % 2 != 0) {
          menuClientPage = menuClientPage - 1;
          menuClientPage = constrain(menuClientPage, 0, maxMenuClientPages);
        }

        cursorPosition = cursorPosition - 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuClientItems) / sizeof(String)) - 1));

        activeButton = 1;
        changeMenu = 1;

        break;
      case 3:
        button = 0;
        if (menuClientPage % 2 == 0 and cursorPosition % 2 != 0) {
          menuClientPage = menuClientPage + 1;
          menuClientPage = constrain(menuClientPage, 0, maxMenuClientPages);
        }

        if (menuClientPage % 2 != 0 and cursorPosition % 2 == 0) {
          menuClientPage = menuClientPage + 1;
          menuClientPage = constrain(menuClientPage, 0, maxMenuClientPages);
        }
        cursorPosition = cursorPosition + 1;
        cursorPosition = constrain(cursorPosition, 0, ((sizeof(menuClientItems) / sizeof(String)) - 1));

        activeButton = 1;
        changeMenu = 1;
        break;
      default:
        break;
    }
  }
}

void at(String _atcm, unsigned long _dl) {
  sim808.print(_atcm + "\r\n");
  delay(_dl);
}

int insert = 0;
void insert_Card() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();


  Serial.println(content);
  Serial.println(content.substring(1));

  //push_data()
  if (Firebase.getInt(content.substring(1)) == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Existing");
    insert = 1;
    delay(1000);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 1);
    insert = 1;
    lcd.print("Accepted");
    delay(1000);
    Firebase.setInt(content.substring(1), 1);
    if (Firebase.failed()) {
      Serial.print("setting failed:");
      Serial.println(Firebase.error());
      return;
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Done");
      delay(1000);
    }
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

bool check_master_RC522() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  if (content.substring(1) == "**************") // MASTER CARD ID
    return true;

  return false;


  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}



bool check_client_RC522() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid));

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();

  if (Firebase.getInt(content.substring(1)) == 1)
    return true;

  return false;


  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void read_DHT() {
  t = dht.readTemperature();
  h = dht.readHumidity();

}

int out = 0;
void read_D2() {
  button_D2 = digitalRead(button);
  if (button_D2 == 1) {
    button_D2 = 0;
    out = 1;
  }

}

void menuItem1() {
  set_time_1(1000);
  read_DHT();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Temp : ");
  lcd.print(t);
  lcd.setCursor(1, 1);
  lcd.print("Humi : ");
  lcd.print(h);
  while (time_flag_1 == 0) {
    read_D2();
    int temp_t = t;
    int temp_h = h;
    read_DHT();
    if (temp_t != t || temp_h != h ) {
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Temp : ");
      lcd.print(t);
      lcd.setCursor(1, 1);
      lcd.print("Humi : ");
      lcd.print(h);
    }
    if (out == 1) {
      out = 0;
      break;
    }
    time_click_1();
    delay(50);
  }

}

void menuItem2() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Uploading...");

  read_DHT();

  Firebase.setFloat("Temperature", t);
  // handle error
  if (Firebase.failed()) {
    return;
  }
  delay(1000);

  Firebase.setFloat("Humidity", h);
  // handle error
  if (Firebase.failed()) {
    return;
  }
  delay(1000);

}

void menuItem3() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Sending...");

  at("AT+CMGF=1", 100);
  at("AT+CMGS=\"SDT\"", 200);
  at("Call 113", 100);
  sim808.write(26);     // ctlrZ

  delay(2000);
}


void menuItem4() { // Insert Card
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("INSERT CARD");

  set_time_1(100);
  while (time_flag_1 == 0) {
    ESP.wdtDisable();
    insert_Card();
    if (insert == 1) {
      insert = 0;
      break;
    }
    time_click_1();
    delay(50);
  }

}

int my_delete = 0;
void delete_Card() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String content = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();

  if (Firebase.getInt(content.substring(1)) == 1) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Deleting...");
    my_delete = 1;
    Firebase.remove(content.substring(1));
    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Done");
    delay(1000);
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 1);
    my_delete = 1;
    lcd.print("Invalid Card");
    delay(1000);

  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}


void menuItem5() { // Delete Card
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("INSERT CARD");

  set_time_1(100);
  while (time_flag_1 == 0) {
    ESP.wdtDisable();
    delete_Card();
    if (my_delete == 1) {
      my_delete = 0;
      break;
    }
    time_click_1();
    delay(50);
  }
}


void menuItem8() {
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Log Out...");


  my_restart = 1;
  change_menu_1 = 1;
  delay(5);
}
