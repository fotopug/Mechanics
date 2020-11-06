#include <Servo.h>
Servo towerprosg5010;
int pos = 0;
void setup()
{
  towerprosg5010.attach(9);
}
void loop()
{
//  for (pos = 0; pos < 180; pos += 1)
//  {
//    towerprosg5010.write(pos);
//    delay(60);
//  }
//  delay(1500);
  for (pos = 180; pos > 0; pos -= 1)
  {
    towerprosg5010.write(pos);
    delay(60);
  }
  towerprosg5010.write(0); //13th floor
    delay(1000);
  towerprosg5010.write(13); //12th floor
    delay(1000);
      towerprosg5010.write(121); // 5th floor
    delay(1000);
  towerprosg5010.write(30); //11th floor
    delay(1000);
  towerprosg5010.write(136); // 4th floor
    delay(1000);
  towerprosg5010.write(62); //9th floor
    delay(1000);
      towerprosg5010.write(164); // 2nd floor
    delay(1000);
  towerprosg5010.write(78); //8th floor
    delay(1000);
  towerprosg5010.write(92); //7th floor
    delay(1000);
      towerprosg5010.write(48); //10th floor
    delay(1000);
  towerprosg5010.write(107); //6th floor
    delay(1000);


  towerprosg5010.write(150); // 3rd floor
    delay(1000);

  towerprosg5010.write(179); // 1st floor
    delay(1000);
}
