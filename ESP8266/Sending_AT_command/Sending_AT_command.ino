
// print output into monitor
// Serial.println("");

// 0: rx , 1:tx
//SoftwareSerial esp(0, 1); if we are using raw ESP and send the AT commands
 

#include "ESP8266WiFi.h"

#define show Serial.println

void setup()
{
    Serial.begin(9600);
}

void loop()
{ 
  
}
