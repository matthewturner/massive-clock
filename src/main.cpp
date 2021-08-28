#include "main.h"

void setup()
{
  Serial.begin(9600);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);
  FastLED.setBrightness(10);

  Serial.println("Setup complete. Continuing...");
}

byte hourCounter = 0;
byte minuteCounter = 0;

void loop()
{
  display.setPart(0, hourCounter, false);
  showDigits();
  delay(2000);
  display.setPart(0, minuteCounter, true);
  showDigits();
  delay(2000);
  display.clear();
  showDigits();
  delay(1000);
  minuteCounter++;
  if (minuteCounter >= 60)
  {
    minuteCounter = 0;
    hourCounter++;
    if (hourCounter >= 24)
    {
      hourCounter = 0;
    }
  }
}

void showDigits()
{
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    if (display.led(i))
    {
      physicalLeds[i] = CRGB::Purple;
    }
    else
    {
      physicalLeds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}