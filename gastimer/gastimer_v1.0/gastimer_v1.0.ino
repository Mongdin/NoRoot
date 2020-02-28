#include <MsTimer2.h>
#include <Servo.h> 

int static interval = 180;
int static interval2 = 12;
int state = 0;
int angle = 0; // servo position in degrees 
volatile int closetime = 0;
volatile int servotime = 0;
volatile int buzzerblink = 0;
int servoPin = 9;
int buttonpin = 2;
int buzzer = 7;
Servo servo; 
void setup() 
{ 
  //Serial.begin(9600);
  pinMode(buttonpin, INPUT_PULLUP); 
  pinMode(buzzer, OUTPUT); 
  attachInterrupt(0,buttonint,FALLING);
  MsTimer2::set(1000, timeadd);
  MsTimer2::start();
  servo_close();
  //Serial.print("started!");
  delay(500);
  servo.detach();
  

} 
void alarm(){
  for(char i = 0;i<10;i++){
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
  }
}

void servo_open() {
  servo.attach(servoPin);
  servotime=3;
  servo.write(0);
}

void servo_close() {
  servo.attach(servoPin);
  servotime=3;
  servo.write(90);
  buzzerblink=0;
}
void buttonint() {
  buzzerblink=0;
  if(state==0) {state=1;}
  else if(state==2) {state=3;}
  //Serial.print("Button Interrupt!!!");
  
}

void timeadd() {
  closetime--;
  if(closetime<=0) {state=0;closetime=0;servo_close();}
  servotime--;
  if(servotime<=0) {servo.detach(); servotime = 0;}
  if(buzzerblink<=0) {
    digitalWrite(buzzer,LOW); buzzerblink=0;
    }
  else
    digitalWrite(buzzer,!digitalRead(buzzer));
}
 



void loop() 
{ 
  //Serial.println(state);
  //Serial.println(closetime);
  
if(state==0) {
  ;
}
else if(state==1) {
  servo_open();
  closetime=interval;
  state=2;
}
else if(state==2) {
  if(closetime<=interval2){
    buzzerblink=1;
  }
}
else if(state==3) {
  buzzerblink=0;
  closetime=interval;
  state=2;
}
delay(100);
} 
