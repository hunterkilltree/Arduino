#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <SoftwareSerial.h>
#include <Ticker.h>


#define debug Serial.println
#define DHTPIN D3
#define DHTTYPE DHT11

#define SolidSensor A0
#define LightSensor D1
#define Relay D4
#define button1 D2
#define button2 D6
#define button3 D7
#define LED_1 D5

#define sda_pin D9 // D9 : rx
#define scl_pin D10 // D10 : tx

#define RX  D0
#define TX  D1

int button_1;
int button_2;
int button_3;

float t; //temperaute
float h; //humidity
int l; // light
float s; //solid
int moisture_percent;

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

void setup_Sensor();
void setup_Relay();
void setup_LED();


void read_DHT();
void read_Solid();
void read_Light();
void read_Button();

void convert_Solid();

void active_Relay();
void deactive_Relay();
void active_LED1();
void deactive_LED1();


Ticker LED_ON;
Ticker RELAY_ON;
int active_RELAY = 0;
int active_LED_1 = 0;

void open_Relay() {
  if (button_1 == 1) {
    if (active_RELAY == 0) {
      active_RELAY = 1;
      active_Relay();
    }
    else if (active_RELAY == 1) {
      active_RELAY = 0;
      deactive_Relay();
    }
  }
}

void open_LED_1() {
  if (button_2 == 1) {
    if (active_LED_1 == 0) {
      active_LED_1 = 1;
      active_LED1();
    }
    else if (active_LED_1 == 1) {
      active_LED_1 = 0;
      deactive_LED1();
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_Sensor();
  setup_Relay();
  setup_LED();

  RELAY_ON.attach(0.4, open_Relay);
  LED_ON.attach(0.5, open_LED_1);
  delay(100);
}



void loop() {
  read_Button();
  read_DHT();
  read_Light();
  read_Solid();
  convert_Solid();


  debug("Buttton 1: ");
  debug(button_1);
  debug("Buttton 2: ");
  debug(button_2);
  debug("Buttton 3: ");
  debug(button_3);


  debug("Light: " );
  debug(l);
  debug("T: " );
  debug(t);
  debug("H: " );
  debug(h);
  debug("Solid" );
  debug(moisture_percent);


  delay(10);
}


void setup_Sensor() {
  dht.begin();
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(SolidSensor, INPUT);
  pinMode(LightSensor, INPUT);

}

void setup_Relay() {
  pinMode(Relay, OUTPUT);
}

void setup_LED() {
  pinMode(LED_1, OUTPUT);
}

void read_DHT() {
  t = dht.readTemperature();
  h = dht.readHumidity();
}

void read_Light() {
  l = digitalRead(LightSensor);
}

void read_Solid() {
  s = analogRead(SolidSensor);
}

void read_Button() {
  button_1 = digitalRead(button1);
  button_2 = digitalRead(button2);
  button_3 = digitalRead(button3);
}

void active_Relay() {
  digitalWrite(Relay, HIGH);
}

void deactive_Relay() {
  digitalWrite(Relay, LOW);
}

void active_LED1() {
  digitalWrite(LED_1, HIGH);
}

void deactive_LED1() {
  digitalWrite(LED_1, LOW);
}

void convert_Solid() {
  moisture_percent = map(s, 0, 1023, 0, 100);
}
