#include "Display.h"

bool Display::led(byte led)
{
  return digitFor(led)->led(offset(led));
}

Digit *Display::digitFor(byte led)
{
  byte digitForLed = led / NUM_DIGITS / LEDS_PER_DIGIT;
  return &_digits[digitForLed];
}

byte Display::offset(byte led)
{
  return led % (NUM_DIGITS * LEDS_PER_DIGIT);
}

void Display::setLed(byte led, bool show)
{
  digitFor(led)->setLed(offset(led), show);
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

void Display::setLedRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    digitFor(i)->setLed(offset(i), show);
  }
}