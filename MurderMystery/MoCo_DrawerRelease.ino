//This code manages a simple box release mechanism with a maglock and 
//Arduino Uno or similar hardware
//LOCKS!
boolean brainLocked = true;
boolean headLocked = true;
boolean boxLocked = true;

//brain switches
int bSwitch[] = {2};

//head switches
int hSwitch[] = {3};

//brain leds
const int bLED_R = 13; //red
const int bLED_Y = 9; //yellow

//head leds
const int hLED_R = 10; //red
const int hLED_Y = 11; //yellow

//box switch
const int boxSwitch = 8;

//box light
const int boxLight = 5;

//box electromagnet
const int masterLock = 12;

//Animation Controls
int currentCycle = 1;
bool cycleReverse = false;

void setup() {
  //Switches
  pinMode(bSwitch[0], INPUT);
  //pinMode(bSwitch[1], INPUT);
  //pinMode(bSwitch[2], INPUT);
  pinMode(hSwitch[0], INPUT);
  //pinMode(hSwitch[1], INPUT);
  //pinMode(hSwitch[2], INPUT);
  pinMode(boxSwitch, INPUT);

  //Lights
  pinMode(bLED_R, OUTPUT);
  pinMode(bLED_Y, OUTPUT);
  pinMode(hLED_R, OUTPUT);
  pinMode(hLED_Y, OUTPUT);
  pinMode(boxLight, OUTPUT);
  digitalWrite(boxLight, LOW);

  //Master Lock
  pinMode(masterLock, OUTPUT);
  //Serial.begin(9600);
}

void loop() {

  //IO - switches and locks
  lockTest(bSwitch[0], hSwitch[0], boxSwitch);

  //ANIMATIONS - clock, brain, head
  clockCycle();
  lockCycle();
}


// FUNCTIONS
int lockTest(int x, int y, int z) {
  int lock1 = digitalRead(x);
  if (lock1 == HIGH && brainLocked == true) {
    brainLocked = false;
  }
  int lock2 = digitalRead(y);
  if (lock2 == HIGH && brainLocked == false) {
    headLocked = false;
    digitalWrite(boxLight, HIGH);
  }
//  int lockMaster = digitalRead(z);
//  if (lockMaster == HIGH && brainLocked == false && headLocked == false) {
//    boxLocked = false;
//    digitalWrite(boxLight, HIGH);
//  }
}

int ledStatic(int ledR, int ledY) {
  digitalWrite(ledR, LOW);
  digitalWrite(ledY, HIGH);
}

int lockCycle() {
  if (brainLocked == true) {
    lockedAnim(bLED_R, bLED_Y);
  } else {
    ledStatic(bLED_R, bLED_Y);
  }
  if (brainLocked == false && headLocked == false) {
    ledStatic(hLED_R, hLED_Y);
  } else {
    if (headLocked == true) {
      lockedAnim(hLED_R, hLED_Y);
    }
  }
}

int lockedAnim(int ledR, int ledY) {
  analogWrite(ledR, currentCycle);
  analogWrite(ledY, 255 - currentCycle);
  delay(2);
}

int clockCycle() {
  if (currentCycle >= 255 && cycleReverse == false) {
    cycleReverse = true;
  } else {
    if (cycleReverse == true && currentCycle >= 1) {
      currentCycle--;
    } else {
      currentCycle++;
      cycleReverse = false;
    }
  }
}
