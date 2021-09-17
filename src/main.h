#ifndef main_h
#define main_h

#include <Arduino.h>
#include <FastLED.h>
#include "Display.h"
#include "Schedule.h"
#include <RTClib.h>
#include <Eventually.h>
#include <LowPower.h>

const short SHOW_TEMPORARILY_DURATION = 3000;
const byte CURRENT_SCHEDULE = SUMMER_SCHEDULE;

const byte DATA_PIN = 3;
const byte CLOCK_PIN = 13;

const byte SHOW_PIN = 6;

const byte SLEEPING = 0;
const byte WORK_PENDING = 1;
const byte IN_PROGRESS = 2;
const byte COMPLETE = 3;

volatile int state;
CRGB physicalLeds[NUM_LEDS];
Display display;
Display pendingDisplay;
RTC_DS3231 clock;
EvtManager mgr;
DateTime now;
Schedule<CRGB::HTMLColorCode> colorSchedule(CRGB::Red);
Schedule<bool> displaySchedule(false);
Schedule<bool> separatorSchedule(false);
Schedule<byte> brightnessSchedule(5);

EvtTimeListener *updateListener;
EvtTimeListener *renderListener;
EvtIntegerListener *showTemporarilyListener;
EvtTimeListener *returnToNormalListener;
EvtTimeListener *sleepListener;

void wakeup();
void render();
void render(CRGB::HTMLColorCode colorCode, byte brightness);
bool update();
bool sleep();
bool showTemporarily();
bool returnToNormal();

void setupColorSchedule();
void setupDisplaySchedule();
void setupBrightnessSchedule();
void setupRealtimeClock();
void setupTest();

#endif