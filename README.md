[![PlatformIO CI](https://github.com/matthewturner/massive-clock/actions/workflows/platformio.yml/badge.svg)](https://github.com/matthewturner/massive-clock/actions/workflows/platformio.yml)

# Massive Clock

A massive 8 segment display with 3 RGB LEDs per segment.

## Schedules

Schedules can be set by sending an encoded 6 digit integer:

```
1             1   4       0   1          2
schedule      hour        block         value
id
```

This example would set the display to minimal for the first half of the 14th hour, ie 14:00-14:30.

## Installing Platform IO

Install command line tools by following the installation instructions for [Windows](https://docs.platformio.org/en/latest/core/installation.html#windows)

## Serial Monitor

Deploy code to your Arduino and run the following command in a terminal:

```powershell
 pio device monitor --eol=CRLF --echo --filter=send_on_enter
```

## Unit Testing

Run the following command after installing Platform IO:

```powershell
pio test -e native
```
