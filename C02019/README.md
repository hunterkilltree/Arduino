# CECO2019

### Hardware Components
 * Aukey 2018 IIC I2C TWI 1602 16 Pins Interface Backlight LCD Dispay Module Board
 * LM2596 DC to DC Buck Converter 3.0-40V to 1.5-35V Power Supply Step Down Module
 *  RFID RC522 NFC 13.56mhz
 * MODULE GSM SIM 800L
 * NODEMCU ESP8266
 * 5 x RESISTORS
 * 3 x BUTTONS
 * 7 x CAPACITORS
 * 1 x DIODES (1N4001)
 * SOME RFID CARDS

### Software
 * Arduino IDE
 * EAGLE PCB design Software
 * Android Studio


## Schematic
![schematic](https://i.imgur.com/bF2LJL7.png)


![photo](https://i.imgur.com/0xTYFDd.jpg)

### PROJECT 1
#### Short Description
Working like a smart room :
* Sensor will read the temperature and humidity  then upload data to DataBase.
* People have the right ID can be access to the room through RFID RC522.
* SIM800L will send message to owner room which shows that RFID RC522 already give access open the door.
* LCD which shows the information about temperature and humidity will be turn on when someone is inside the room.
* Button 3 working as an switch when people go outside press button 3 to lock the system.

##### Instruction Manual :
* Using RFID CARDS to access through  RFID RC522.
* Press Button 3  put system into sleep mode.


### PROJECT 2
#### Short Description
I will call this project name "Master and His Slavers":
* Master have it own ID which is can not change
    * He can watch the information of environment around, upload data to his own server, send message to call help.
    * On the other hand, he has power to add many Slavers as he want to his system or delete them.

* Slavers have to work for his master (if their ID already allow through master)
    * They have 3 basic work that looking for the temperature around, upload the data to mater server so that he can what the temperature and humidity through his smartphone.
    * ![smartphone](https://i.imgur.com/gJL56Bb.png)
    * They can send message if something go wrong.

#### Instruction Manual:
* At the beginning, people have 2 choice log in as Master or Slavers
    * Press 1 to log in as Master => go to Master's menu
    * Press 2 to log in as Slavers => go to Slavers' menu
* Menu :
    * Press 1 to go Up.
    * Press 2 to go Down.
    * Press 1 + 2 to enter the mode.
* In mode "Display temperature and humidity" back to main menu press button 3.

* Note: When "Insert Card" is waiting to long (6 second) it will back to the previous menu.



## REQUIRE KNOWLEDGE + key word
* Basic DataBase
* Multiple button inputs
* Android Studio mobile app design
* Basic Arduino coding
* EAGLE PCB design

### Video
* (^_^) Subcribe my channel to watch more project next time.
* https://youtu.be/YuC8cK49fA8
