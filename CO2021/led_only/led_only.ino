#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define LED_0 D0
#define LED_1 D1
#define LED_2 D2
#define LED_3 D3
#define LED_4 D4
#define LED_5 D5
#define LED_6 D6
#define LED_7 D7
#define LED_8 D8
#define LED_9 D9
#define LED_10 D10
const int LED_11 =  A0;
 

#define FIREBASE_HOST "*************************"
#define FIREBASE_AUTH "*************************"
#define WIFI_SSID "*************************"
#define WIFI_PASSWORD "*************************"
 
 
 
void setup_8266();
void setup_firebase();
 
 
void open_led();
void close_led();
 
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_0, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  pinMode(LED_11, OUTPUT);
  setup_8266();
  setup_firebase();
 
  open_led();
  close_led();
 
}
 
float temp;
int maxtemp;
void loop() {
  temp = Firebase.getFloat("Temperature");
  maxtemp = Firebase.getInt("MaxTemp");
 
  if (temp < maxtemp) {
    digitalWrite(LED_7, LOW);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
  }
  else if (temp >= maxtemp + 2 && temp < maxtemp + 4) {
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, LOW);
    digitalWrite(LED_9, LOW);
  }
  else if (temp >= maxtemp + 4 && temp < maxtemp + 6) {
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, LOW);
  }
  else if (temp >= maxtemp + 6) {
    digitalWrite(LED_7, HIGH);
    digitalWrite(LED_8, HIGH);
    digitalWrite(LED_9, HIGH);
  }
 
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
 
 
void open_led() {
  digitalWrite(LED_0, LOW);
  delay(1000);
  digitalWrite(LED_0, HIGH);
  delay(2000);
  digitalWrite(LED_1, LOW);
  delay(1000);
  digitalWrite(LED_1, HIGH);
  delay(2000);
  digitalWrite(LED_2, LOW);
  delay(1000);
  digitalWrite(LED_2, HIGH);
  delay(2000);
 
  digitalWrite(LED_3, LOW);
  delay(1000);
  digitalWrite(LED_3, HIGH);
  delay(2000);
 
  digitalWrite(LED_4, LOW);
  delay(1000);
  digitalWrite(LED_4, HIGH);
  delay(2000);
 
  digitalWrite(LED_5, LOW);
  delay(1000);
  digitalWrite(LED_5, HIGH);
  delay(2000);
 
  digitalWrite(LED_6, LOW);
  delay(1000);
  digitalWrite(LED_6, HIGH);
  delay(2000);
 
  digitalWrite(LED_7, LOW);
  delay(1000);
  digitalWrite(LED_7, HIGH);
  delay(2000);
 
  digitalWrite(LED_8, LOW);
  delay(1000);
  digitalWrite(LED_8, HIGH);
  delay(2000);
 
  digitalWrite(LED_9, LOW);
  delay(1000);
  digitalWrite(LED_9, HIGH);
  delay(2000);
 
 
  digitalWrite(LED_10, LOW);
  delay(1000);
  digitalWrite(LED_10, HIGH);
  delay(2000);
 
  digitalWrite(LED_11, LOW);
  delay(1000);
  digitalWrite(A0, HIGH);
  delay(2000);
}
 
 
void close_led() {
  digitalWrite(LED_0, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  digitalWrite(LED_5, LOW);
  digitalWrite(LED_6, LOW);
  digitalWrite(LED_7, LOW);
  digitalWrite(LED_8, LOW);
  digitalWrite(LED_9, LOW);
  digitalWrite(LED_10, LOW);
  digitalWrite(LED_11, LOW);
}
