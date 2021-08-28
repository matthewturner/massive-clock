#ifndef main_h
#define main_h

#include <Arduino.h>
#include <FastLED.h>
#include "Display.h"
#include <RTClib.h>

const byte DATA_PIN = 3;
const byte CLOCK_PIN = 13;

CRGB physicalLeds[NUM_LEDS];
Display display;
RTC_DS3231 clock;
void showDigits();
#endif