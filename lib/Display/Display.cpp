#include "Display.h"

bool Display::led(byte led)
{
  return componentFor(led)->led(offset(led));
}

Component *Display::componentFor(byte led)
{
  byte componentForLed = led / NUM_DIGITS / LEDS_PER_DIGIT;
  return &_digits[componentForLed];
}

byte Display::offset(byte led)
{
  byte offset = led % (NUM_DIGITS * LEDS_PER_DIGIT);
  return offset;
}

void Display::setLed(byte led, bool show)
{
  componentFor(led)->setLed(offset(led), show);
}

void Display::clear()
{
  for (byte i = 0; i < NUM_DIGITS; i++)
  {
    _digits[i].clear();
  }
}

void Display::setDigit(byte digit, byte value)
{
  _digits[digit].set(value);
}

void Display::setPart(byte part, byte value, bool leadingZero)
{
  byte offset = part * 2;
  byte tens = (value - (value % 10)) / 10;
  byte unit = value % 10;
  setDigit(0 + offset, unit);
  if (leadingZero || tens > 0)
  {
    setDigit(1 + offset, tens);
  }
}

void Display::setLedRange(byte first, byte last, bool show)
{
  for (byte i = first; i <= last; i++)
  {
    componentFor(i)->setLed(offset(i), show);
  }
}

bool Display::updateFrom(Display *other)
{
  bool updated = false;
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    if (led(i) != other->led(i))
    {
      setLed(i, other->led(i));
      updated = true;
    }
  }
  return updated;
}

void Display::setSeparator(bool show)
{
}