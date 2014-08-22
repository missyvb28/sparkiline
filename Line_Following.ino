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

int speedLeft;
int speedRight;

void setup() 
{
  speedLeft = 100;
  speedRight = 100;
}

void loop() {
  int deadband = 10;

  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor

  if ((lineLeft - deadband) > lineRight) { // Off-center to the right
    speedLeft -= 5;
    speedRight += 5;
  } else if ((lineRight - deadband) > lineLeft) { // Off-center to the left
    speedLeft += 5;
    speedRight -= 5;
  } else {
    if (speedRight > speedLeft)
      speedLeft = speedRight;
    else
      speedRight = speedLeft;
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
  
  sparki.updateLCD(); // display all of the information written to the screen

  delay(100); // wait 0.1 seconds
}
