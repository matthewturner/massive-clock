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
  byte remaining = led;
  for (byte i = 0; i < NUM_COMPONENTS; i++)
  {
    if (remaining < _components[i]->ledCount())
    {
      return _components[i];
    }
    remaining -= _components[i]->ledCount();
  }
  return nullptr;
}

byte Display::offset(byte led)
{
  byte remaining = led;
  for (byte i = 0; i < NUM_COMPONENTS; i++)
  {
    if (remaining < _components[i]->ledCount())
    {
      return remaining;
    }
    remaining -= _components[i]->ledCount();
  }
  return remaining;
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
  if (offset > 0)
  {
    offset++;
  }
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
  _separator.setAll(show);
}