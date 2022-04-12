#ifndef main_h
#define main_h

#include <Arduino.h>
#include <FastLED.h>
#include "Display.h"
#include "Schedule.h"
#include <RTClib.h>
#include <Eventually.h>
#include <LowPower.h>
#include <SoftwareSerial.h>
#include "CommandReader.h"
#include "RuntimeStreamReader.h"

const short SHOW_TEMPORARILY_DURATION = 3000;
const byte CURRENT_SCHEDULE = SUMMER_SCHEDULE;

const byte DATA_PIN = 3;
const byte CLOCK_PIN = 13;
const byte TRANSMIT_PIN = 5;
const byte RECEIVE_PIN = 6;

const byte SHOW_PIN = 2;
const bool CLOCK_IS_ENABLED = true;

const byte IDLE = 0;
const byte PENDING = 1;
const byte IN_PROGRESS = 2;

volatile byte state = IDLE;
volatile byte *pState = &state;
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
Schedule<Flags> minimalSchedule(Flags::NONE);
SoftwareSerial bluetoothSerial(RECEIVE_PIN, TRANSMIT_PIN);
RuntimeStreamReader streamReader(&bluetoothSerial);
Command command;
CommandReader commandReader(&streamReader);

EvtTimeListener *updateListener;
EvtTimeListener *commandListener;
EvtTimeListener *renderListener;
EvtByteListener *showTemporarilyListener;
EvtTimeListener *returnToNormalListener;
EvtByteListener *sleepListener;

void setState(byte state);
void wakeup();
void render();
void render(CRGB::HTMLColorCode colorCode, byte brightness);
bool update();
bool sleep();
bool showTemporarily();
bool returnToNormal();
bool process();

void setupColorSchedule();
void setupDisplaySchedule();
void setupBrightnessSchedule();
void setupRealtimeClock();
void setupMinimalModeSchedule();
void setupTest();

#endif