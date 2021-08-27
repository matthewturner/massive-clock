#include "Display.h"

bool Display::led(byte led)
{
  return _leds[led];
}

void Display::clear()
{
  bufferAllSegments(false);
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    _leds[i] = false;
  }
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
  for (byte s = 0; s < SEGMENTS_PER_DIGIT; s++)
  {
    for (byte i = 0; i < LEDS_PER_SEGMENT; i++)
    {
      _leds[i + (s * LEDS_PER_SEGMENT) + offset] = _segments[s];
    }
  }
}

void Display::bufferDigit(byte value)
{
  bufferAllSegments(true);

  switch (value)
  {
  case 0:
    bufferSegment(SEG_MIDDLE, false);
    break;
  case 1:
    bufferSegment(SEG_TOP_LEFT, false);
    bufferSegment(SEG_TOP, false);
    bufferSegment(SEG_MIDDLE, false);
    bufferSegment(SEG_BOTTOM_LEFT, false);
    bufferSegment(SEG_BOTTOM, false);
    break;
  case 2:
    bufferSegment(SEG_TOP_LEFT, false);
    bufferSegment(SEG_BOTTOM_RIGHT, false);
    break;
  case 3:
    bufferSegment(SEG_TOP_LEFT, false);
    bufferSegment(SEG_BOTTOM_LEFT, false);
    break;
  case 4:
    bufferSegment(SEG_TOP, false);
    bufferSegment(SEG_TOP_RIGHT, false);
    bufferSegment(SEG_BOTTOM_LEFT, false);
    bufferSegment(SEG_BOTTOM, false);
    break;
  case 5:
    bufferSegment(SEG_TOP_RIGHT, false);
    bufferSegment(SEG_BOTTOM_LEFT, false);
    break;
  case 6:
    bufferSegment(SEG_TOP_RIGHT, false);
    break;
  case 7:
    bufferSegment(SEG_TOP_LEFT, false);
    bufferSegment(SEG_BOTTOM_LEFT, false);
    bufferSegment(SEG_BOTTOM, false);
    break;
  case 9:
    bufferSegment(SEG_BOTTOM_LEFT, false);
    break;
  }
}

void Display::bufferAllSegments(bool show)
{
  for (byte i = 0; i < SEGMENTS_PER_DIGIT; i++)
  {
    _segments[i] = show;
  }
}

void Display::bufferSegment(byte segment, bool show)
{
  _segments[segment] = show;
}

void Display::setSegmentRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    _segments[i] = show;
  }
}

void Display::setLedRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    _leds[i] = show;
  }
}