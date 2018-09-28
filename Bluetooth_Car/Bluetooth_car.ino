#include <AFMotor.h>

AF_DCMotor m1(1);
AF_DCMotor m2(4);

AF_DCMotor m3(2);
AF_DCMotor m4(3);

void setup() {

  Serial.begin(9600);
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m4.setSpeed(255);
}

void loop() {
  String temp = "";
  while(Serial.available()){//kepping read
    delay(50); // choose the time
    temp += (char)Serial.read(); // take the input from the Ch-06
  }

  if (temp.length()){

    if (temp == "FORWARD"){
      forward();
    }
    else if (temp == "BACKWARD"){
      backward();
    }
    else if (temp == "LEFT"){
      left();
    }
    else if (temp == "RIGHT"){
      right();
    }    
   }
 }
 
void left(){
  m1.run(FORWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
  m4.run(FORWARD);
  delay(500);
  Stop();
}

void right(){
  m1.run(BACKWARD);
  m2.run(BACKWARD);
  m3.run(BACKWARD);
  m4.run(BACKWARD);
  Serial.print("left");
  delay(500);
  Stop();
}

void forward(){
   m1.run(BACKWARD);
   m2.run(FORWARD);
   m3.run(BACKWARD);
   m4.run(FORWARD);
   delay(2000);
   Stop();
}

void backward(){
   m1.run(FORWARD);
   m2.run(BACKWARD);
   m3.run(FORWARD);
   m4.run(BACKWARD);
   delay(2000);
   Stop();
}

void Stop(){
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
}






