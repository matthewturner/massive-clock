#include "main.h"

void setup()
{
  Serial.begin(9600);

  pinMode(SHOW_PIN, INPUT_PULLUP);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);
  FastLED.setBrightness(5);

  while (!Serial)
    ;

  setupRealtimeClock();
  setupColorSchedule();
  setupDisplaySchedule();
  setupBrightnessSchedule();
  setupTest();

  updateListener = new EvtTimeListener(500, true, (EvtAction)update);
  mgr.addListener(updateListener);

  showTemporarilyListener = new EvtPinListener(SHOW_PIN, 100, LOW, (EvtAction)showTemporarily);
  mgr.addListener(showTemporarilyListener);
  returnToNormalListener = new EvtTimeListener(SHOW_TEMPORARILY_DURATION, true, (EvtAction)returnToNormal);
  returnToNormalListener->enabled = false;
  mgr.addListener(returnToNormalListener);

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  mgr.loopIteration();
}

bool update()
{
  now = clock.now();

  if (displaySchedule.valueFor(now.hour()))
  {
    display.setPart(1, now.hour(), false);
    display.setPart(0, now.minute(), true);
  }
  else
  {
    display.clear();
  }

  display.setSeparator(displaySchedule.valueFor(now.hour()));
  render();

  return false;
}

bool showTemporarily()
{
  Serial.println("Showing temporarily...");
  showTemporarilyListener->disable();
  updateListener->disable();
  returnToNormalListener->enable();

  now = clock.now();
  display.setPart(1, now.hour(), false);
  display.setPart(0, now.minute(), true);
  display.setSeparator(true);
  render();

  return false;
}

bool returnToNormal()
{
  Serial.println("Returning to normal...");
  returnToNormalListener->disable();
  updateListener->enable();
  showTemporarilyListener->enable();

  return false;
}

void render()
{
  byte brightness = brightnessSchedule.valueFor(now.hour());
  FastLED.setBrightness(brightness);

  CRGB::HTMLColorCode colorCode = colorSchedule.valueFor(now.hour());

  for (byte i = 0; i < NUM_LEDS; i++)
  {
    if (display.led(i))
    {
      physicalLeds[i] = colorCode;
    }
    else
    {
      physicalLeds[i] = CRGB::Black;
    }
  }

  FastLED.show();
}

void setupColorSchedule()
{
  Serial.println("Setup color schedule...");
  // daylight
  colorSchedule.setup(8, 20, CRGB::Blue);
  // morning
  colorSchedule.setup(6, 7, CRGB::Orange);
  // evening
  colorSchedule.setup(21, 21, CRGB::Purple);
}

void setupDisplaySchedule()
{
  Serial.println("Setting up display schedule...");

  separatorSchedule.setup(6, 10, true);
  separatorSchedule.setup(19, 21, true);
  displaySchedule.setup(19, 21, true);

  if (CURRENT_SCHEDULE == SUMMER_SCHEDULE)
  {
    displaySchedule.setup(6, 10, true);
  }
  else
  {
    displaySchedule.setup(7, 10, true);
  }
}

void setupBrightnessSchedule()
{
  Serial.println("Setting up brightness schedule...");
  brightnessSchedule.setup(10, 18, 40);
}

void setupRealtimeClock()
{
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
  if (digitalRead(SHOW_PIN) == LOW)
  {
    Serial.println("Manual override: setting the time...");
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void setupTest()
{
  Serial.println("Testing display 88...");
  display.setPart(0, 88, false);
  render();
  delay(200);
  display.clear();
  display.setSeparator(true);
  render();
  delay(200);
  display.clear();
  display.setPart(1, 88, false);
  render();
  delay(200);
  display.clear();
}