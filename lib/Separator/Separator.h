#ifndef Separator_h
#define Separator_h

#include "common.h"
#include "Component.h"

const byte LEDS_IN_SEPARATOR = 2;

class Separator : public Component
{
public:
    bool led(byte led) override;
    void set(byte value) override;
    void setLed(byte led, bool show) override;
    void setRange(byte first, byte last, bool show);
    void show();
    void hide();
    void clear() override;
    void setAll(bool show);
    byte ledCount() override;

private:
    bool _leds[LEDS_IN_SEPARATOR];
};

#endif