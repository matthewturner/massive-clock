#ifndef main_h
#define main_h

#include <Arduino.h>
#include <FastLED.h>
#include "Display.h"
#include "Schedule.h"
#include <RTClib.h>
#include <Eventually.h>

const byte DATA_PIN = 3;
const byte CLOCK_PIN = 13;

CRGB physicalLeds[NUM_LEDS];
Display display;
RTC_DS3231 clock;
EvtManager mgr;
DateTime now;
Schedule<CRGB::HTMLColorCode> colorSchedule(CRGB::Red);
Schedule<bool> displaySchedule(false);

void render();
bool update();

void setupColorCodes();
void setupDisplayHours();
void setupRealtimeClock();
void setupTest();

#endif