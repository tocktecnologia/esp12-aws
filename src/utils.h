#ifndef UTILS_H
#define UTILS_H

#include <ESP8266WiFi.h>
const int LED = 2;
unsigned long LedsSequence[4]; //[x] is the number of leds array

void blinkLed(int led, int interval, int array, int repeat)
{
  if ((int)((long)millis() - LedsSequence[array]) >= interval)
  {
    LedsSequence[array] = millis(); // stores the millis value in the selected array
    digitalWrite(LED, !digitalRead(LED)); // changes led state
  }
}

#endif //UTILS_H