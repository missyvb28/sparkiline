/*******************************************
 Sparki Line-following example
 
 Threshold is the value that helps you 
 determine what's black and white. Sparki's 
 infrared reflectance sensors indicate white 
 as close to 900, and black as around 200.
 This example uses a threshold of 500 for 
 the example, but if you have a narrow line, 
 or perhaps a lighter black, you may need to 
 adjust.
********************************************/

#include <Sparki.h> // include the sparki library

#define BASESPEED 100

int speedLeft;
int speedRight;

void setup() 
{
  speedLeft = BASESPEED;
  speedRight = BASESPEED;
}

void loop() {
  int deadband = 1;

  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  int lineDiff = lineLeft - lineRight;

  lineDiff = lineDiff / 50;

  if (lineDiff < -deadband) {
    speedRight += lineDiff;
    speedLeft = BASESPEED;
  } else if (lineDiff > deadband) {
    speedLeft -= lineDiff;
    speedRight = BASESPEED;
  } else {
    speedLeft = BASESPEED;
    speedRight = BASESPEED;
  }

  sparki.motorRotate(MOTOR_LEFT, DIR_CCW, speedLeft);
  sparki.motorRotate(MOTOR_RIGHT, DIR_CW, speedRight);

  sparki.clearLCD(); // wipe the screen
  
  sparki.print("Line Left: "); // show left line sensor on screen
  sparki.println(lineLeft);
  
  sparki.print("Line Center: "); // show center line sensor on screen
  sparki.println(lineCenter);
  
  sparki.print("Line Right: "); // show right line sensor on screen
  sparki.println(lineRight);

  sparki.print("Speed Left: ");
  sparki.println(speedLeft);

  sparki.print("lineDiff: ");
  sparki.println(lineDiff);

  sparki.print("Speed Right: ");
  sparki.println(speedRight);

  sparki.updateLCD(); // display all of the information written to the screen

  delay(100); // wait 0.1 seconds
}
