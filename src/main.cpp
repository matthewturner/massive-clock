#include "main.h"

Dependency dependency;

void setup()
{
  Serial.begin(9600);

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  if (dependency.method())
  {
    Serial.println("Was true");
  }
}

#include <FastLED.h>

#define NUM_LEDS 60

#define DATA_PIN 3
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];

void setup()
{
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
}

void loop()
{
  setDigit(0, 0);
  FastLED.show();
  delay(30);
}

void setDigit(byte digit, byte value)
{
  switch (value)
  {
  case 0:
    leds[digit + 0] = CRGB::Blue;
    leds[digit + 1] = CRGB::Blue;
    leds[digit + 2] = CRGB::Blue;
    leds[digit + 3] = CRGB::Blue;
    leds[digit + 4] = CRGB::Blue;
    leds[digit + 5] = CRGB::Blue;
    leds[digit + 8] = CRGB::Blue;
    leds[digit + 9] = CRGB::Blue;
    leds[digit + 10] = CRGB::Blue;
    leds[digit + 11] = CRGB::Blue;
    leds[digit + 12] = CRGB::Blue;
    leds[digit + 13] = CRGB::Blue;
    break;
  }
}
