#include <unity.h>
#include <stdio.h>
#include "test_separator.h"

Separator target;
Separator expected;

void setUp(void)
{
    expected.clear();
    target.clear();
}

void test_segment_half(void)
{
    expected.setRange(0, 0, true);
    target.setLed(0, true);
    assert();
}

void test_segment_full(void)
{
    expected.setRange(0, 1, true);
    target.show();
    assert();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_segment_half);
    RUN_TEST(test_segment_full);
    UNITY_END();

    return 0;
}

void assert()
{
    for (byte i = 0; i < LEDS_IN_SEPARATOR; i++)
    {
        char buffer[30];
        if (expected.led(i))
        {
            int n = sprintf(buffer, "Expected %d to be true", i);
            TEST_ASSERT_TRUE_MESSAGE(target.led(i), buffer);
        }
        else
        {
            int n = sprintf(buffer, "Expected %d to be false", i);
            TEST_ASSERT_FALSE_MESSAGE(target.led(i), buffer);
        }
    }
}