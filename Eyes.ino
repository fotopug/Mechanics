#include <Servo.h>
Servo towerprosg5010b;
int pos = 0;
int throwswitch = 2;
int switchstate = 0;

void setup()
{
  towerprosg5010b.attach(9);
}
void loop()
{
  switchstate = digitalRead(throwswitch);
  if (switchstate == HIGH) {
//  for (pos = 40; pos < 160; pos += 1)
//  {
//    towerprosg5010b.write(pos);
//    delay(60);
//  }
//  delay(1000);
  towerprosg5010b.write(40); //left
  delay(500);
  towerprosg5010b.write(105); //return to center
  delay(1000);
  towerprosg5010b.write(160); //right
  delay(500);
  towerprosg5010b.write(105); //return to center
  delay(1000);
  towerprosg5010b.write(40); //left
  delay(500);
  towerprosg5010b.write(105); //return to center
  delay(1000);
  towerprosg5010b.write(40); //left
  delay(500);
  towerprosg5010b.write(105); //return to center
  delay(1000);
  towerprosg5010b.write(160); //right
  delay(500);
  towerprosg5010b.write(105); //return to center
  delay(4000);
} else {
    delay(100);
  }   
}
