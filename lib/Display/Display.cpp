#include "Display.h"

bool Display::led(byte led)
{
  return _leds[led];
}

void Display::clear()
{
  for (byte i = 0; i < 4; i++)
  {
    _digits[i].clear();
  }
}

void Display::setDigit(byte digit, byte value)
{
  _digits[digit].set(value);
}

void Display::setPart(byte part, byte value)
{
  byte offset = part * 2;
  setDigit(0 + offset, value % 10);
  bufferDigit(1 + offset, (value - (value % 10)) / 10);
}

// void Display::setSegmentRange(byte first, byte last, bool show)
// {
//   for (byte i = first; i <= last; i++)
//   {
//     _segments[i] = show;
//   }
// }

// void Display::setLedRange(byte first, byte last, bool show)
// {
//   for (byte i = first; i <= last; i++)
//   {
//     _leds[i] = show;
//   }
// }