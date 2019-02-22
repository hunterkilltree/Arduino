const int Green_LED = 13;


int state = 0;
int time_flag = 0;
int time_counter = 0;


void set_time(int value) {
  time_counter = value;
  time_flag = 0;
}

void time_click(){
  if(time_counter > 0){
    time_counter--;
    if(time_counter == 0)
      time_flag = 1;
    
  }
}


void setup() {
  Serial.begin(9600);
  state = 1; // 0: nothing ; 1: start;
  time_flag = 1;

  pinMode(Green_LED, OUTPUT);
}

void loop() {
  switch(state){
    case 1 :  
      if (time_flag == 1) {
        Serial.write("Acting\n");
        digitalWrite(Green_LED, HIGH);
        set_time(50);
        state = 0;      
      }
      break;
    case 0:
      if (time_flag == 1){
        digitalWrite(Green_LED, LOW);
        set_time(30);
        state = 1;
      }
      break;
    default:
      break;
  }

  time_click();
  delay(1);
}
