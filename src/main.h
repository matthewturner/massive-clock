#ifndef main_h
#define main_h

#include <Arduino.h>
#include <FastLED.h>
#include "Display.h"
#include "Schedule.h"
#include <RTClib.h>
#include <Timezone.h>
#include <Eventually.h>
#include <EvtCommandListener.h>
#include <EvtStateMachineListener.h>
#include <LowPower.h>
#include <SoftwareSerial.h>

const short SHOW_TEMPORARILY_DURATION = 3000;
const byte CURRENT_SCHEDULE = SUMMER_SCHEDULE;

const byte DATA_PIN = 3;
const byte CLOCK_PIN = 13;
const byte TRANSMIT_PIN = 5;
const byte RECEIVE_PIN = 6;

const byte SHOW_PIN = 2;
const bool CLOCK_IS_ENABLED = true;

const byte IDLE = 0;
const byte UPDATING = 1;
const byte PROCESSING = 2;
const byte SHOWING = 3;

CRGB physicalLeds[NUM_LEDS];
Display display;
Display pendingDisplay;
RTC_DS3231 clock;
EvtManager mgr;
Timezone *timezone;
Schedule<CRGB::HTMLColorCode> colorSchedule(CRGB::Red);

Schedule<bool> displaySchedule(false, 1);
Schedule<bool> separatorSchedule(false);
Schedule<byte> brightnessSchedule(5);
Schedule<Flags> minimalSchedule(Flags::NONE);
SoftwareSerial bluetoothSerial(RECEIVE_PIN, TRANSMIT_PIN);
EvtCommandListener commandListener(&bluetoothSerial);
EvtStateMachineListener stateMachine;

void onInterrupt();
void render();
void render(CRGB::HTMLColorCode colorCode, byte brightness);
bool updating();
bool idle();
bool showing();
bool show();
bool set(EvtListener *, EvtContext *, long data);
bool setSchedule(EvtListener *, EvtContext *, long data);
bool status();

void reportStatus();
DateTime toLocal(DateTime utc);

void setupColorSchedule();
void setupDisplaySchedule();
void setupBrightnessSchedule();
void setupRealtimeClock();
void setupMinimalModeSchedule();
void setupTimezones();
void setupTest();

#endif