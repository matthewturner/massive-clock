#ifndef main_h
#define main_h

#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 60

const byte LEDS_PER_SEGMENT = 2;
const byte SEGMENTS_PER_DIGIT = 7;
const byte LEDS_IN_SEPARATOR = 2;
const byte LEDS_PER_DIGIT = LEDS_PER_SEGMENT * SEGMENTS_PER_DIGIT;

const byte SEG_TOP_LEFT = 0;
const byte SEG_TOP = SEG_TOP_LEFT + LEDS_PER_SEGMENT;
const byte SEG_TOP_RIGHT = SEG_TOP + LEDS_PER_SEGMENT;
const byte SEG_MIDDLE = SEG_TOP_RIGHT + LEDS_PER_SEGMENT;
const byte SEG_BOTTOM_LEFT = SEG_MIDDLE + LEDS_PER_SEGMENT;
const byte SEG_BOTTOM = SEG_BOTTOM_LEFT + LEDS_PER_SEGMENT;
const byte SEG_BOTTOM_RIGHT = SEG_BOTTOM + LEDS_PER_SEGMENT;

const byte DATA_PIN = 3;
const byte CLOCK_PIN = 13;

CRGB physicalLeds[NUM_LEDS];
bool segments[LEDS_PER_DIGIT];
bool leds[NUM_LEDS];

void setDigit(byte digit, byte value);
void setIndividualDigit(byte value);
void applyDigit(byte digit);
void setSegment(byte segment, bool show);
void showSegment(byte segment);
void hideSegment(byte segment);
void showAllSegments();
void showDigits();
#endif