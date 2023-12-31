#include "blinkLED.h"
const int firstLedPin  = 13; // choose the pin for each of the LEDs
const int secondLedPin = 5;
const int thirdLedPin  = 6;

void setup()
{
  pinMode(firstLedPin, OUTPUT);  // declare LED pins as output
  pinMode(secondLedPin, OUTPUT); // declare LED pins as output
  pinMode(thirdLedPin, OUTPUT);  // declare LED pins as output
}

void loop()
{
  // flash each of the LEDs for 1000 milliseconds (1 second)
  blinkLED(firstLedPin,  1000);
  blinkLED(secondLedPin, 1000);
  blinkLED(thirdLedPin,  1000);
}
