#include "Display.h"

bool Display::led(byte led)
{
  byte digitForLed = led / 4 / LEDS_PER_DIGIT;
  byte ledInDigit = led % (4 * LEDS_PER_DIGIT);
  return _digits[digitForLed].led(ledInDigit);
}

void Display::setLed(byte led, bool show)
{
  byte digitForLed = led / 4 / LEDS_PER_DIGIT;
  byte ledInDigit = led % (4 * LEDS_PER_DIGIT);
  _digits[digitForLed].setLed(ledInDigit, show);
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
  setDigit(1 + offset, (value - (value % 10)) / 10);
}

// void Display::setSegmentRange(byte first, byte last, bool show)
// {
//   for (byte i = first; i <= last; i++)
//   {
//     _segments[i] = show;
//   }
// }

void Display::setLedRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    byte digitForLed = i / 4 / LEDS_PER_DIGIT;
    byte ledInDigit = i % (4 * LEDS_PER_DIGIT);
    _digits[digitForLed].setLed(ledInDigit, show);
  }
}