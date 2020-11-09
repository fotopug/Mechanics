//outputs
int audioPin = 4;
int lockcirc1 = 5;
int lockcirc2 = 6;

//inputs
int codeswitch1 = 8;
int codeswitch2 = 9;
int codeswitch3 = 10;

//store values for inputs
int codeswitch1state = 0;
int codeswitch2state = 0;
int codeswitch3state = 0;

//story solve states
int code1solved = 0;
int code2solved = 0;
int code3solved = 0;
int fullysolved = 0;

//audio playback state
int audioplayed = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello!");
  //set pinmode for outputs
  pinMode(audioPin, OUTPUT);
  pinMode(lockcirc1, OUTPUT);
  pinMode(lockcirc2, OUTPUT);
  //set pinmode for inputs
  pinMode(codeswitch1, INPUT);
  pinMode(codeswitch2, INPUT);
  pinMode(codeswitch3, INPUT);
}

void loop() {
  //set all the relays low so they don't trip
  digitalWrite(audioPin, LOW);
  digitalWrite(lockcirc1, LOW);
  digitalWrite(lockcirc2, LOW);
  codeswitch1state = digitalRead(codeswitch1);
  codeswitch2state = digitalRead(codeswitch2);
  codeswitch3state = digitalRead(codeswitch3);
//  Serial.println(codeswitch3state);
  //determine order of locks and whether they've been unlocked or not
  //code1 solution
  if (codeswitch1state == HIGH && code1solved == 0) {
    code1solved = 1;
    Serial.println("lock 1 unlocked");
    digitalWrite(lockcirc1, HIGH);
    delay(1000);
  }
  //code2 solution
  if (codeswitch2state == HIGH && code1solved == 1) {
    code2solved = 1;
    Serial.println("lock 2 unlocked");
    digitalWrite(lockcirc2, HIGH);
    delay(5000);
  }
  //code3 solution
  if (codeswitch3state == HIGH && code2solved == 1 && audioplayed == 0) {
    delay(5000);
    if (codeswitch3state == HIGH && fullysolved == 0) {
      fullysolved = 1;
      delay(2000);
    }
    if (codeswitch3state == HIGH && fullysolved == 1) {
      code3solved = 1;
      audioplayed = 1;
      digitalWrite(audioPin, HIGH);
      delay(5000);
      Serial.println("lock 3 unlocked");
    }
  }
}