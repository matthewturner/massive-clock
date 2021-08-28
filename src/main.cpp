#include "main.h"

void setup()
{
  Serial.begin(9600);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);
  FastLED.setBrightness(10);

  while (!Serial)
    ;

  if (!clock.begin())
  {
    Serial.println("Couldn't find Realtime Clock");
    Serial.flush();
    abort();
  }

  if (clock.lostPower())
  {
    Serial.println("Realtime Clock lost power, setting the time...");
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  Serial.println("Testing display 88...");
  display.setPart(0, 88, false);
  delay(500);

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  DateTime now = clock.now();
  byte hour = now.hour();
  byte minute = now.minute();
  Serial.print(hour);
  Serial.print(":");
  Serial.println(minute);

  display.setPart(0, hour, false);
  showDigits();
  delay(2000);
  display.setPart(0, minute, true);
  showDigits();
  delay(2000);
  display.clear();
  showDigits();
  delay(1000);
}

void showDigits()
{
  for (byte i = 0; i < NUM_LEDS; i++)
  {
    if (display.led(i))
    {
      physicalLeds[i] = CRGB::Purple;
    }
    else
    {
      physicalLeds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}