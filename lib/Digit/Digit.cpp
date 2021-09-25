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
  switch (count)
  {
  case 1:
    _leds[15] = true;
    break;
  case 2:
    _leds[15] = true;
    _leds[16] = true;
    break;
  case 3:
    _leds[15] = true;
    _leds[16] = true;
    _leds[17] = true;
    break;
  case 4:
    _leds[15] = true;
    _leds[16] = true;
    _leds[17] = true;

    _leds[11] = true;
    break;
  case 5:
    _leds[15] = true;
    _leds[16] = true;
    _leds[17] = true;

    _leds[11] = true;
    _leds[10] = true;
    break;
  case 6:
    _leds[15] = true;
    _leds[16] = true;
    _leds[17] = true;

    _leds[11] = true;
    _leds[10] = true;
    _leds[9] = true;
    break;
  case 7:
    _leds[15] = true;
    _leds[16] = true;
    _leds[17] = true;

    _leds[11] = true;
    _leds[10] = true;
    _leds[9] = true;

    _leds[3] = true;
    break;
  case 8:
    _leds[15] = true;
    _leds[16] = true;
    _leds[17] = true;

    _leds[11] = true;
    _leds[10] = true;
    _leds[9] = true;

    _leds[3] = true;
    _leds[4] = true;
    break;
  case 9:
    _leds[15] = true;
    _leds[16] = true;
    _leds[17] = true;

    _leds[11] = true;
    _leds[10] = true;
    _leds[9] = true;

    _leds[3] = true;
    _leds[4] = true;
    _leds[5] = true;
    break;
  }
}