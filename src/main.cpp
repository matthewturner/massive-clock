#include "main.h"

void setup()
{
  Serial.begin(9600);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);
  FastLED.setBrightness(10);

  Serial.println("Setup complete. Continuing...");
}

byte counter = 0;

void loop()
{
  display.setPart(0, counter);
  display.setPart(1, counter);
  showDigits();
  counter++;
  if (counter >= 100)
  {
    counter = 0;
  }
  delay(400);
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