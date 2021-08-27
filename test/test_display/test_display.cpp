#include <unity.h>
#include <stdio.h>
#include "test_display.h"

Display target;
Display expected;

void setUp(void)
{
    expected.clear();
    target.clear();
}

void test_first_digit_eight(void)
{
    target.setDigit(0, 8);
    expected.setLedRange(0, 13, true);
    assert();
}

void test_first_digit_zero(void)
{
    target.setDigit(0, 0);
    expected.setLedRange(0, 5, true);
    expected.setLedRange(8, 13, true);
    assert();
}

void test_first_digit_one(void)
{
    target.setDigit(0, 1);
    expected.setLedRange(4, 5, true);
    expected.setLedRange(12, 13, true);
    assert();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_first_digit_eight);
    RUN_TEST(test_first_digit_zero);
    RUN_TEST(test_first_digit_one);
    UNITY_END();

    return 0;
}

void assert()
{
    for (byte i = 0; i < NUM_LEDS; i++)
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