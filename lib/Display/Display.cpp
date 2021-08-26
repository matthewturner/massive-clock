#include "Display.h"

bool Display::led(byte led)
{
  return _leds[led];
}

void Display::setDigit(byte digit, byte value)
{
  bufferDigit(value);
  applyDigit(digit);
}

void Display::setPart(byte part, byte value)
{
  byte offset = part * 2;
  bufferDigit(value % 10);
  applyDigit(0 + offset);
  bufferDigit((value - (value % 10)) / 10);
  applyDigit(1 + offset);
}

void Display::applyDigit(byte digit)
{
  byte offset = LEDS_PER_DIGIT * digit;
  if (digit > 1)
  {
    offset += LEDS_IN_SEPARATOR;
  }
  for (byte i = 0; i < LEDS_PER_DIGIT; i++)
  {
    _leds[i + offset] = _segments[i];
  }
}

void Display::bufferDigit(byte value)
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

void Display::showAllSegments()
{
  for (byte i = 0; i < LEDS_PER_DIGIT; i++)
  {
    _segments[i] = true;
  }
}

void Display::showSegment(byte segment)
{
  setSegment(segment, true);
}

void Display::hideSegment(byte segment)
{
  setSegment(segment, false);
}

void Display::setSegment(byte segment, bool show)
{
  for (byte i = 0; i < LEDS_PER_SEGMENT; i++)
  {
    _segments[segment + i] = show;
  }
}