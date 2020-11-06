int uvled = 11;
int primarylight = 10;
int throwswitch = 9;
int brightness = 50;
int fadeAmount = 1;
int switchstate = 0;
bool poweron = false;

void setup() {
  pinMode(uvled, OUTPUT);
  pinMode(primarylight, OUTPUT);
  pinMode(throwswitch, INPUT);
}

void loop() {
  //reset to dark
  analogWrite(uvled,0);
  analogWrite(primarylight,10);
  delay(1000);
  //cue throwswitch input and read the state of the switch:
  switchstate = digitalRead(throwswitch);
  // check if the pushbutton is pressed.
  if (switchstate == HIGH) {
    //animate lights on
  analogWrite(primarylight,100);
  delay(50);
  analogWrite(primarylight,0);
  delay(30);
  analogWrite(primarylight,100);
  delay(50);
  analogWrite(primarylight,0);
  delay(100);
  analogWrite(primarylight,75);
  delay(200);
  analogWrite(primarylight,0);
  delay(100);
  //elevator rises
  analogWrite(uvled,0);
  analogWrite(primarylight,255);
  delay(28000);
  //animate light failure
  analogWrite(primarylight,0);
  delay(100);
  analogWrite(primarylight,255);
  delay(100);
  analogWrite(primarylight,0);
  delay(40);
  analogWrite(primarylight,255);
  delay(30);
  analogWrite(primarylight,0);
  delay(40);
  analogWrite(primarylight,255);
  delay(30);
  analogWrite(primarylight,0);
  delay(40);
  analogWrite(primarylight,255);
  delay(200);
  analogWrite(primarylight,0);
  delay(300);
  analogWrite(uvled,150);
  delay(30);
  analogWrite(uvled,75);
  delay(100);
  analogWrite(uvled,0);
  delay(100);
  analogWrite(uvled,40);
  delay(80);
  analogWrite(uvled,0);
  delay(400);
  analogWrite(uvled,brightness);
  //ensure brightness is zero
  while (brightness > 0) {
    brightness = 0;
  }
  // animate uv light on
  while (brightness < 255) {
    analogWrite(uvled,brightness);
    brightness = brightness + fadeAmount;
    delay(30);
  }
  brightness = 0;
  delay(3000); 
  switchstate = 0; 
  } else {
    delay(100);
  }                
}
