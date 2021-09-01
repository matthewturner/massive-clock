#include "Display.h"

Display::Display()
{
}

bool Display::led(byte led)
{
  return componentFor(led)->led(offset(led));
}

Component *Display::componentFor(byte led)
{
  byte componentForLed = led / LEDS_PER_DIGIT;
  return _components[componentForLed];
}

byte Display::offset(byte led)
{
  byte offset = led % LEDS_PER_DIGIT;
  return offset;
}

void Display::setLed(byte led, bool show)
{
  componentFor(led)->setLed(offset(led), show);
}

void Display::clear()
{
  for (byte i = 0; i < NUM_COMPONENTS; i++)
  {
    _components[i]->clear();
  }
}

void Display::setDigit(byte digit, byte value)
{
  _components[digit]->set(value);
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