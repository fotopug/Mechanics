//This script is responsible for controlling a variety of motion control
//systems, listening for voltages that correspond to button presses, and
//metaphorically unlocking doors. Its primary concern are elevator events
//libraries
//libraries
#include <Servo.h>
//this section reserved for painting eye servo
Servo towerprosg5010a;
Servo towerprosg5010b;

//this variable sets the position of the eyes
int pos = 0;

//these variables are the RFID read values and pins
int bellhopRFIDpin = A2;
int bellhopRFIDvalue = 0;

//this variable is how we check whether we've received a signal yet or not
int eyestatus = 0;

//this section reserved for door entrance control
int elevatorDoorPin = 10;
int elevatorDoorReleasePin = 5;
int elevatordoorstate = 0;
int elevatordoorsafety = 0;
int eyesdisable = 0;

//this section reserved for hoist and hoist relay
int throwswitchPin = 2;
int relayHoistPin = 4;
int switchstate = 0;
int hoiststate = 0;

//elevator vibration trigger
int relayaudiopin = 6;
int audioswitch01state = 0;

//elevator animation system disabled
int animationcomplete = 0;

//attach a pin to open the rear doors automatically
int reardoortriggerpin = 12;

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
  //rear elevator door trigger
  pinMode(reardoortriggerpin,OUTPUT);
  //set the indicator to the first floor
  towerprosg5010b.write(179); // 1st floor
  //general serial output 
  Serial.begin(9600);
}

void loop() {
    //ensure that rear door relay is off
    digitalWrite(reardoortriggerpin,HIGH);
    //ensure the hoist relay switch is off
    digitalWrite(relayHoistPin,HIGH);
    //check that the front door has not been opened, ensure the maglock remains locked
    if (elevatordoorsafety ==  0) {
      digitalWrite(elevatorDoorReleasePin,HIGH);
      delay(100);
    }
    //ensure the vibration system relay is off
    digitalWrite(relayaudiopin,HIGH);
    //this stores the current state of whether the throwswitch is closed or open
    switchstate = digitalRead(throwswitchPin);
    //this stores the current state of the UP button in front of the elevator door
    elevatordoorstate = digitalRead(elevatorDoorPin);
    //this stores whether we are receiving voltage from the RFID reader or not. 
    bellhopRFIDvalue = analogRead(bellhopRFIDpin);
    //serialized IFs, needs to have better approach. This section for front elevator door.
    //if the elevator door button isn't being pressed, do nothing
    if (elevatordoorstate == 0) {
      Serial.print(elevatordoorstate);
    } else {
      //if the elevator door button is being pressed, shut off the maglock
      Serial.print(elevatordoorstate);
      digitalWrite(elevatorDoorReleasePin,LOW);
      delay(500);
      //set the safety value to true to disable the maglock for good
      elevatordoorsafety = 1;
      eyesdisable = 1;
    }
    //serialized IFs, needs to have better approach. This section for eyeballs.
    Serial.println(bellhopRFIDvalue);
    if (bellhopRFIDvalue > 1000 && eyesdisable == 0) {
      //this is a simple animation that continues for as long as the RFID is sending a high voltage
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
      delay(4000);
    }
    //this is the default, open hoist switch state. Nothing is happening.
    if (switchstate == 1 && animationcomplete == 0) {
      //this conditionally turns the relay on. Reset is dependent on the top of the loop.
      Serial.print(switchstate);
      //power up the hoist
      digitalWrite(relayHoistPin,LOW);
      //power up the rumble
      digitalWrite(relayaudiopin,LOW);
      delay(500);
      towerprosg5010b.write(179); // 1st floor
      delay(500);
      towerprosg5010b.write(164); // 2nd floor
      delay(500);
      towerprosg5010b.write(150); // 3rd floor
      delay(500);
      towerprosg5010b.write(136); // 4th floor
      delay(500);
      towerprosg5010b.write(121); // 5th floor
      delay(500);
      towerprosg5010b.write(107); //6th floor
      delay(500);
      towerprosg5010b.write(92); //7th floor
      delay(500);
      towerprosg5010b.write(78); //8th floor
      delay(500);
      towerprosg5010b.write(62); //9th floor
      delay(500);
      towerprosg5010b.write(48); //10th floor
      delay(500);
      towerprosg5010b.write(30); //11th floor
      delay(500);
      towerprosg5010b.write(13); //12th floor
      digitalWrite(relayaudiopin,HIGH);
      delay(500);
      towerprosg5010b.write(0); //13th floor
      digitalWrite(relayHoistPin,HIGH);
      animationcomplete = 1;
      digitalWrite(reardoortriggerpin,LOW);
      delay(1000);
    } else {
      //do nothing
    }
}
