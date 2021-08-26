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
  setDigit(0, counter);
  setDigit(1, counter);
  setDigit(2, counter);
  setDigit(3, counter);
  showDigits();
  counter++;
  if (counter >= 10)
  {
    counter = 0;
  }
  delay(100);
}

void setDigit(byte digit, byte value)
{
  setIndividualDigit(value);
  applyDigit(digit);
}

void applyDigit(byte digit)
{
  byte offset = LEDS_PER_DIGIT * digit;
  if (digit > 1)
  {
    offset += LEDS_IN_SEPARATOR;
  }
  for (byte i = 0; i < LEDS_PER_DIGIT; i++)
  {
    leds[i + offset] = segments[i];
  }
}

void setIndividualDigit(byte value)
{
  showAllSegments();

  switch (value)
  {
  case 0:
    hideSegment(SEG_MIDDLE);
    break;
  case 1:
    hideSegment(SEG_TOP_LEFT);
    hideSegment(SEG_TOP);
    hideSegment(SEG_MIDDLE);
    hideSegment(SEG_BOTTOM_LEFT);
    hideSegment(SEG_BOTTOM);
    break;
  case 2:
    hideSegment(SEG_TOP_LEFT);
    hideSegment(SEG_BOTTOM_RIGHT);
    break;
  case 3:
    hideSegment(SEG_TOP_LEFT);
    hideSegment(SEG_BOTTOM_LEFT);
    break;
  case 4:
    hideSegment(SEG_TOP);
    hideSegment(SEG_TOP_RIGHT);
    hideSegment(SEG_BOTTOM_LEFT);
    hideSegment(SEG_BOTTOM);
    break;
  case 5:
    hideSegment(SEG_TOP_RIGHT);
    hideSegment(SEG_BOTTOM_LEFT);
    break;
  case 6:
    hideSegment(SEG_TOP_RIGHT);
    break;
  case 7:
    hideSegment(SEG_TOP_LEFT);
    hideSegment(SEG_BOTTOM_LEFT);
    hideSegment(SEG_BOTTOM);
    break;
  case 9:
    hideSegment(SEG_BOTTOM_LEFT);
    break;
  }
}

void showAllSegments()
{
  for (byte i = 0; i < LEDS_PER_DIGIT; i++)
  {
    segments[i] = true;
  }
}

void showSegment(byte segment)
{
  setSegment(segment, true);
}

void hideSegment(byte segment)
{
  setSegment(segment, false);
}

void setSegment(byte segment, bool show)
{
  for (byte i = 0; i < LEDS_PER_SEGMENT; i++)
  {
    segments[segment + i] = show;
  }
}

void showDigits()
{
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    if (leds[i])
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