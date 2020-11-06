//This script is responsible for controlling a variety of motion control
//systems, listening for voltages that correspond to button presses, and
//metaphorically unlocking doors. Its primary concern are elevator events
//libraries
#include <Servo.h>
//this section reserved for painting eye servo
Servo towerprosg5010a;
Servo towerprosg5010b;
int pos = 0;
int bellhopRFIDpin = A2;
int bellhopRFIDvalue = 0;

//this section reserved for door entrance control
int elevatorDoorPin = 10;
int elevatorDoorReleasePin = 5;
int elevatordoorstate = 0;
int elevatordoorsafety = 0;

//this section reserved for hoist and hoist relay
int throwswitchPin = 2;
int relayHoistPin = 4;
int switchstate = 0;
int hoiststate = 0;

//elevator audio trigger
int relayaudiopin = 6;
int audioswitch01state = 0;

//application
void setup() {
  //painting eye attach to pin 9 and input on 
  towerprosg5010a.attach(9);
  pinMode(bellhopRFIDpin,INPUT);
  //elevator interior floor indicator
  towerprosg5010b.attach(11);
  //elevator rw
  pinMode(elevatorDoorReleasePin,OUTPUT);
  pinMode(elevatorDoorPin,INPUT);
  //hoist rw
  pinMode(relayHoistPin,OUTPUT);
  pinMode(throwswitchPin,INPUT);
  //audio rw
  pinMode(relayaudiopin,OUTPUT);
  //general serial output 
  Serial.begin(9600);
}

void loop() {
    digitalWrite(relayHoistPin,HIGH);
    if (elevatordoorsafety ==  0) {
    digitalWrite(elevatorDoorReleasePin,HIGH);
    delay(100);
    }
    digitalWrite(relayaudiopin,HIGH);
    switchstate = digitalRead(throwswitchPin);
    elevatordoorstate = digitalRead(elevatorDoorPin);
    bellhopRFIDvalue = analogRead(bellhopRFIDpin);
    //serialized IFs, needs to have better approach. This section for front elevator door.
    if (elevatordoorstate == 0) {
      Serial.print(elevatordoorstate);
    } else {
      Serial.print(elevatordoorstate);
      digitalWrite(elevatorDoorReleasePin,LOW);
      delay(500);
      elevatordoorsafety = 1;
    }
    //serialized IFs, needs to have better approach. This section for eyeballs.
    Serial.println(bellhopRFIDvalue);
    if (bellhopRFIDvalue > 1000) {
      towerprosg5010a.write(40); //left
      delay(500);
      towerprosg5010a.write(105); //return to center
      delay(1000);
      towerprosg5010a.write(160); //right
      delay(500);
      towerprosg5010a.write(105); //return to center
      delay(1000);
      towerprosg5010a.write(40); //left
      delay(500);
      towerprosg5010a.write(105); //return to center
      delay(1000);
      towerprosg5010a.write(40); //left
      delay(500);
      towerprosg5010a.write(105); //return to center
      delay(1000);
      towerprosg5010a.write(160); //right
      delay(500);
      towerprosg5010a.write(105); //return to center
      delay(100);
    }
    //this is the default, open switch state. Nothing is happening.
    if (switchstate == 0) {
      Serial.print(switchstate);
    } else {
      //this conditionally turns the relay on. Reset is dependent on the top of the loop.
      Serial.print(switchstate);
      digitalWrite(relayHoistPin,LOW);
      digitalWrite(relayaudiopin,LOW);
      delay(1000);
        towerprosg5010b.write(0); //13th floor
    delay(1000);
  towerprosg5010b.write(13); //12th floor
    delay(1000);
      towerprosg5010b.write(121); // 5th floor
    delay(1000);
  towerprosg5010b.write(30); //11th floor
    delay(1000);
  towerprosg5010b.write(136); // 4th floor
    delay(1000);
  towerprosg5010b.write(62); //9th floor
    delay(1000);
      towerprosg5010b.write(164); // 2nd floor
    delay(1000);
  towerprosg5010b.write(78); //8th floor
    delay(1000);
  towerprosg5010b.write(92); //7th floor
    delay(1000);
      towerprosg5010b.write(48); //10th floor
    delay(1000);
  towerprosg5010b.write(107); //6th floor
    delay(1000);
  towerprosg5010b.write(150); // 3rd floor
    delay(1000);
  towerprosg5010b.write(179); // 1st floor
    delay(1000);
    }
}
