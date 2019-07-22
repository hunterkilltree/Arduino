/*
 Created:	7/19/2019 10:55:11 PM
 Author:	hunterkill
 Des : run 11 led on my own circuit with 4 main modes.
*/

#include <ESP8266WiFi.h>

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
const int LED_11 = A0;

void setup_led();
void open_led();
void close_led();

void middle_run();
void both_side();
void tail_run();
void head_run();

void setup() {
	setup_led();
	open_led();
	close_led();
}

void loop() {
	close_led();
	middle_run();
	close_led();
	both_side();
	close_led();
	head_run();
	close_led();
	tail_run();
}

void setup_led() {
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

void middle_run() {
	delay(300);

	digitalWrite(LED_4, HIGH);
	digitalWrite(LED_6, HIGH);
	delay(300);

	digitalWrite(LED_3, HIGH);
	digitalWrite(LED_7, HIGH);
	delay(300);

	digitalWrite(LED_2, HIGH);
	digitalWrite(LED_8, HIGH);
	delay(300);

	digitalWrite(LED_1, HIGH);
	digitalWrite(LED_9, HIGH);
	delay(300);

	digitalWrite(LED_0, HIGH);
	digitalWrite(LED_10, HIGH);
	delay(300);

	digitalWrite(LED_5, HIGH);
	delay(300);
}

void tail_run() {
	delay(200);
	digitalWrite(LED_10, HIGH);
	delay(200);
	digitalWrite(LED_9, HIGH);
	delay(200);
	digitalWrite(LED_8, HIGH);
	delay(200);
	digitalWrite(LED_7, HIGH);
	delay(200);
	digitalWrite(LED_6, HIGH);
	delay(200);
	digitalWrite(LED_5, HIGH);
	delay(200);
	digitalWrite(LED_4, HIGH);
	delay(200);
	digitalWrite(LED_3, HIGH);
	delay(200);
	digitalWrite(LED_2, HIGH);
	delay(200);
	digitalWrite(LED_1, HIGH);
	delay(200);
	digitalWrite(LED_0, HIGH);
	delay(200);
}

void head_run() {
	delay(200);
	digitalWrite(LED_0, HIGH);
	delay(200);
	digitalWrite(LED_1, HIGH);
	delay(200);
	digitalWrite(LED_2, HIGH);
	delay(200);
	digitalWrite(LED_3, HIGH);
	delay(200);
	digitalWrite(LED_4, HIGH);
	delay(200);
	digitalWrite(LED_5, HIGH);
	delay(200);
	digitalWrite(LED_6, HIGH);
	delay(200);
	digitalWrite(LED_7, HIGH);
	delay(200);
	digitalWrite(LED_8, HIGH);
	delay(200);
	digitalWrite(LED_9, HIGH);
	delay(200);
	digitalWrite(LED_10, HIGH);
	delay(200);
	digitalWrite(LED_11, HIGH);
}

void both_side() {
	delay(150);
	digitalWrite(LED_0, HIGH);
	digitalWrite(LED_10, HIGH);
	delay(150);

	digitalWrite(LED_1, HIGH);
	digitalWrite(LED_9, HIGH);
	delay(150);

	digitalWrite(LED_2, HIGH);
	digitalWrite(LED_8, HIGH);
	delay(150);

	digitalWrite(LED_3, HIGH);
	digitalWrite(LED_7, HIGH);
	delay(150);

	digitalWrite(LED_4, HIGH);
	digitalWrite(LED_6, HIGH);
	delay(150);

	digitalWrite(LED_5, HIGH);
	delay(150);
}
