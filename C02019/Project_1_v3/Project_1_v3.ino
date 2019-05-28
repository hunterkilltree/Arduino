/*
   In this project, we use Nodemcu as an main processor :
    RC522        ESP8266
   Signal          Pin
   RST/Reset       D4
   SPI SS          D8
   SPI MOSI        D7
   SPI MISO        D6
   SPI SCK         D5

*/

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "DHT.h"

#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>  // Library for Mifare RC522 Devices

#include <SoftwareSerial.h>


const int button = 4; // D2

#define DHTPIN D3
#define DHTTYPE DHT11

#define sda_pin D9 // D9 : rx
#define scl_pin D10 // D10 : tx

#define RST_PIN D4          // Configurable, see typical pin layout above
#define SS_PIN  D8          // Configurable, see typical pin layout above

#define RX  D0
#define TX  D1


//Server Firebase
#define FIREBASE_HOST "************************"
#define FIREBASE_AUTH "************************"


//AP
#define WIFI_SSID ************************"
#define WIFI_PASSWORD "************************"

// Phone 
String SDT = "************************";
float t; //temperaute
float h; //humidity

#define analogPin A0
#define debug Serial.println

int buttonVal; // store value from the analog pin

// prototype function
void buttonCheck(); //Checks which button or button combo has been pressed
void process();



SoftwareSerial sim808(TX, RX);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(TX, RX);

// prototype
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
bool check_RC522();
bool outdoor();

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

void loop() {
  read_DHT();

  updateData();

  if (check_RC522() == true) {
    lcd.backlight();   
    send_message(); 
  }

  if (outdoor() == true) {
    lcd.noBacklight();
  }

  delay(100);
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
  lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
  delay(100);
  
  Wire.begin(sda_pin, scl_pin); // Wire.begin(SDA, SCL)
  delay(200);


  // Bắt buộc quét qua từng ô
  lcd.setCursor(0, 0);
  lcd.print("000000000000000");
  delay(100);
  int i;
  for (i = 0; i < 16; i++) {
    lcd.setCursor(i, 1);
    lcd.print('0');
    delay(100);
  }

  lcd.clear();
}

void LCD_display() {
  lcd.setCursor(1, 0);
  lcd.print("Welcome home");
  delay(100);
  lcd.setCursor(1, 1);
  lcd.print("T ");
  lcd.print(t);
  lcd.print(" ");
  lcd.print("H ");
  lcd.print(h);
}


void read_DHT() {
  t = dht.readTemperature();
  h = dht.readHumidity();
  LCD_display();
  delay(1000);
}

bool check_RC522() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return false;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return false;
  }

  String content = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  content.toUpperCase();
  if (content.substring(1) == "**************") // Your ID Card
    return true;

  if (content.substring(1) == "*****************") // Your ID Card
    return true;

  return false;
}

bool outdoor() {
  if (digitalRead(button))
    return false;
  return true;

}

void at(String _atcm, unsigned long _dl) {
  sim808.print(_atcm + "\r\n");
  delay(_dl);
}

void send_message() {

  at("AT+CMGF=1",1000);
  at("AT+CMGS=\"0338103740\"",2000);
  at("Someone open the door",1000);
  sim808.write(26);    
}

void updateData() {
  Firebase.setFloat("Temperature", t);
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
