#ifndef main_h
#define main_h

#include <Arduino.h>
#include <FastLED.h>
#include "Display.h"
#include <RTClib.h>
#include <Eventually.h>

const byte DATA_PIN = 3;
const byte CLOCK_PIN = 13;

const byte HOUR = 0;
const byte MINUTE = 1;
const byte NOTHING = 2;
const byte HOURS_IN_DAY = 24;

CRGB physicalLeds[NUM_LEDS];
Display display;
RTC_DS3231 clock;
EvtManager mgr;
DateTime now;
byte showing = 0;

void showDigits();
bool showTime();
CRGB::HTMLColorCode determineColorCode();
void populateColorCodes();
CRGB::HTMLColorCode colorCodesForHour[HOURS_IN_DAY];
#endif