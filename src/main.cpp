#include "main.h"

void setup()
{
  Serial.begin(9600);

  pinMode(SHOW_PIN, INPUT_PULLUP);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(physicalLeds, NUM_LEDS);

  while (!Serial)
    ;

  setupRealtimeClock();
  setupColorSchedule();
  setupDisplaySchedule();
  setupBrightnessSchedule();
  setupMicroModeSchedule();
  setupTest();

  updateListener = new EvtTimeListener(0, true, (EvtAction)update);
  mgr.addListener(updateListener);

  sleepListener = new EvtByteListener(pState, IDLE, (EvtAction)sleep);
  mgr.addListener(sleepListener);

  showTemporarilyListener = new EvtByteListener(pState, PENDING, (EvtAction)showTemporarily);
  mgr.addListener(showTemporarilyListener);

  returnToNormalListener = new EvtTimeListener(SHOW_TEMPORARILY_DURATION, true, (EvtAction)returnToNormal);
  returnToNormalListener->disable();
  mgr.addListener(returnToNormalListener);

  attachInterrupt(digitalPinToInterrupt(SHOW_PIN), wakeup, LOW);

  Serial.println("Setup complete. Continuing...");
}

void loop()
{
  mgr.loopIteration();
}

void wakeup()
{
  if (state == IDLE)
  {
    setState(PENDING);
  }
}

bool sleep()
{
  Serial.println("Sleeping...");
  Serial.flush();
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_OFF, TWI_OFF);
  return true;
}

bool update()
{
  Serial.println("Updating...");

  if (CLOCK_IS_ENABLED)
  {
    now = clock.now();
  }

  if (displaySchedule.valueFor(now.hour()))
  {
    if (microSchedule.valueFor(now.hour()))
    {
      pendingDisplay.setPart(1, now.hour(), Flags::MICRO);
      pendingDisplay.setPart(0, now.minute(), (Flags)(Flags::LEADING_ZERO | Flags::MICRO));
      pendingDisplay.setSeparator(false);
    }
    else
    {
      pendingDisplay.setPart(1, now.hour(), Flags::NONE);
      pendingDisplay.setPart(0, now.minute(), Flags::LEADING_ZERO);
      pendingDisplay.setSeparator(true);
    }
  }
  else
  {
    pendingDisplay.clear();
  }

  CRGB::HTMLColorCode colorCode = colorSchedule.valueFor(now.hour());
  pendingDisplay.setColor(colorCode);
  byte brightness = brightnessSchedule.valueFor(now.hour());
  pendingDisplay.setBrightness(brightness);

  if (display.updateFrom(&pendingDisplay))
  {
    render();
  }

  return true;
}

void setState(byte newState)
{
  Serial.print("Setting state: ");
  switch (newState)
  {
  case PENDING:
    Serial.println("PENDING");
    break;
  case IN_PROGRESS:
    Serial.println("IN_PROGRESS");
    break;
  case IDLE:
    Serial.println("IDLE");
    break;
  }
  state = newState;
}

bool showTemporarily()
{
  Serial.println("Showing temporarily...");
  setState(IN_PROGRESS);

  updateListener->disable();
  returnToNormalListener->enable();

  if (CLOCK_IS_ENABLED)
  {
    now = clock.now();
  }
  display.setPart(1, now.hour(), Flags::NONE);
  display.setPart(0, now.minute(), Flags::LEADING_ZERO);
  display.setSeparator(true);

  CRGB::HTMLColorCode colorCode = colorSchedule.valueFor(now.hour());
  display.setColor(colorCode);
  byte brightness = brightnessSchedule.valueFor(now.hour());
  display.setBrightness(brightness);

  render();

  return true;
}

bool returnToNormal()
{
  Serial.println("Returning to normal...");
  returnToNormalListener->disable();
  updateListener->enable();

  setState(IDLE);

  return true;
}

void render()
{
  FastLED.setBrightness(display.getBrightness());
  CRGB::HTMLColorCode colorCode = (CRGB::HTMLColorCode)display.getColor();

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
    displaySchedule.setup(6, 9, true);
  }
  else
  {
    displaySchedule.setup(7, 9, true);
  }
}

void setupBrightnessSchedule()
{
  Serial.println("Setting up brightness schedule...");
  brightnessSchedule.setup(10, 18, 40);
}

void setupMicroModeSchedule()
{
  Serial.println("Setting up micro mode schedule...");
  brightnessSchedule.setup(6, 7, true);
}

void setupRealtimeClock()
{
  if (!CLOCK_IS_ENABLED)
  {
    Serial.println("Clock is disabled");
    now = DateTime(2014, 1, 21, 3, 0, 0);
    return;
  }

  display.setBrightness(20);
  display.setColor(CRGB::Red);

  if (!clock.begin())
  {
    Serial.println("Couldn't find Realtime Clock");
    Serial.flush();
    display.setText("cloc");
    render();
    delay(1000);
    abort();
  }

  if (clock.lostPower())
  {
    Serial.println("Realtime Clock lost power, setting the time...");
    display.setText("lost");
    render();
    delay(1000);
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  if (digitalRead(SHOW_PIN) == LOW)
  {
    Serial.println("Manual override: setting the time...");
    display.setText("rset");
    render();
    delay(1000);
    clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void setupTest()
{
  Serial.println("Testing display 88...");
  display.setPart(0, 88, Flags::NONE);
  display.setBrightness(20);
  display.setColor(CRGB::Blue);
  render();
  delay(200);
  display.clear();
  display.setSeparator(true);
  render();
  delay(200);
  display.clear();
  display.setPart(1, 88, Flags::NONE);
  render();
  delay(200);
  display.clear();
  display.setText("ello");
  display.setColor(CRGB::Green);
  render();
  delay(500);
  display.clear();
}