#include "Digit.h"

bool Digit::led(byte led)
{
  return _leds[led];
}

void Digit::clear()
{
  for (byte i = 0; i < LEDS_PER_DIGIT; i++)
  {
    setLed(i, false);
  }
}

byte Digit::ledCount()
{
  return LEDS_PER_DIGIT;
}

void Digit::set(byte value)
{
  setAll(true);

  switch (value)
  {
  case 0:
    setSegment(SEG_MIDDLE, false);
    break;
  case 1:
    setSegment(SEG_TOP_LEFT, false);
    setSegment(SEG_TOP, false);
    setSegment(SEG_MIDDLE, false);
    setSegment(SEG_BOTTOM_LEFT, false);
    setSegment(SEG_BOTTOM, false);
    break;
  case 2:
    setSegment(SEG_TOP_LEFT, false);
    setSegment(SEG_BOTTOM_RIGHT, false);
    break;
  case 3:
    setSegment(SEG_TOP_LEFT, false);
    setSegment(SEG_BOTTOM_LEFT, false);
    break;
  case 4:
    setSegment(SEG_TOP, false);
    setSegment(SEG_BOTTOM_LEFT, false);
    setSegment(SEG_BOTTOM, false);
    break;
  case 5:
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_BOTTOM_LEFT, false);
    break;
  case 6:
    setSegment(SEG_TOP_RIGHT, false);
    break;
  case 7:
    setSegment(SEG_TOP_LEFT, false);
    setSegment(SEG_MIDDLE, false);
    setSegment(SEG_BOTTOM_LEFT, false);
    setSegment(SEG_BOTTOM, false);
    break;
  case 9:
    setSegment(SEG_BOTTOM_LEFT, false);
    break;
  case 'r':
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_TOP, false);
    setSegment(SEG_TOP_LEFT, false);
    setSegment(SEG_BOTTOM_RIGHT, false);
    setSegment(SEG_BOTTOM, false);
    break;
  case 'e':
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_BOTTOM_RIGHT, false);
    break;
  case 's':
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_BOTTOM_LEFT, false);
    break;
  case 't':
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_TOP, false);
    setSegment(SEG_BOTTOM_RIGHT, false);
    break;
  case 'l':
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_TOP, false);
    setSegment(SEG_MIDDLE, false);
    setSegment(SEG_BOTTOM_RIGHT, false);
    break;
  case 'c':
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_TOP, false);
    setSegment(SEG_TOP_LEFT, false);
    setSegment(SEG_BOTTOM_RIGHT, false);
    break;
  case 'o':
    setSegment(SEG_TOP_RIGHT, false);
    setSegment(SEG_TOP, false);
    setSegment(SEG_TOP_LEFT, false);
    break;
  case ' ':
    setAll(false);
    break;
  }
}

void Digit::setAll(bool show)
{
  for (byte i = 0; i < LEDS_PER_DIGIT; i++)
  {
    setLed(i, show);
  }
}

void Digit::setSegment(byte segment, bool show)
{
  for (byte i = 0; i < LEDS_PER_SEGMENT; i++)
  {
    _leds[i + (segment * LEDS_PER_SEGMENT)] = show;
  }
}

void Digit::fillSegment(byte segment, byte max)
{
  byte startIndex = segment * LEDS_PER_SEGMENT;
  switch (segment)
  {
  case SEG_TOP_RIGHT:
  case SEG_TOP:
  case SEG_BOTTOM:
  case SEG_BOTTOM_LEFT:
    for (byte i = 0; i < max; i++)
    {
      _leds[i + startIndex] = true;
    }
    break;
  default:
    for (byte i = LEDS_PER_SEGMENT - max; i < LEDS_PER_SEGMENT; i++)
    {
      _leds[i + startIndex] = true;
    }
    break;
  }
}

void Digit::setSegmentRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    setSegment(i, show);
  }
}

void Digit::setLedRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    setLed(i, show);
  }
}

void Digit::setLed(byte led, bool show)
{
  _leds[led] = show;
}

void Digit::setDots(byte count)
{
  setAll(false);

  byte overflow = count % LEDS_PER_SEGMENT;
  byte layers = count / LEDS_PER_SEGMENT;
  switch (layers)
  {
  case 0:
    fillSegment(SEG_BOTTOM, overflow);
    break;
  case 1:
    fillSegment(SEG_BOTTOM, LEDS_PER_SEGMENT);
    fillSegment(SEG_MIDDLE, overflow);
    break;
  case 2:
    fillSegment(SEG_BOTTOM, LEDS_PER_SEGMENT);
    fillSegment(SEG_MIDDLE, LEDS_PER_SEGMENT);
    fillSegment(SEG_TOP, overflow);
    break;
  case 3:
    fillSegment(SEG_BOTTOM, LEDS_PER_SEGMENT);
    fillSegment(SEG_MIDDLE, LEDS_PER_SEGMENT);
    fillSegment(SEG_TOP, LEDS_PER_SEGMENT);
    break;
  }
}