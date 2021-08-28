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
    expected.setLedRange(0, 20, true);
    target.setDigit(0, 8);
    assert();
}

void test_first_digit_zero(void)
{
    expected.setLedRange(0, 8, true);
    expected.setLedRange(12, 20, true);
    target.setDigit(0, 0);
    assert();
}

void test_first_digit_one(void)
{
    expected.setLedRange(0, 2, true);
    expected.setLedRange(12, 14, true);
    target.setDigit(0, 1);
    assert();
}

void test_second_digit_three(void)
{
    expected.setLedRange(21, 26, true);
    expected.setLedRange(30, 38, true);
    target.setDigit(1, 3);
    assert();
}

void test_part_no_leading_zero(void)
{
    expected.setLedRange(0, 20, true);
    target.setPart(0, 8, false);
    assert();
}

void test_part_with_leading_zero(void)
{
    expected.setLedRange(0, 41, true);
    expected.setLedRange(30, 32, false);
    target.setPart(0, 8, true);
    assert();
}

void test_update_from_returns_false_if_no_update_required(void)
{
    TEST_ASSERT_FALSE(target.updateFrom(&expected));
}

void test_update_from_returns_true_if_update_required(void)
{
    expected.setLed(1, true);
    TEST_ASSERT_TRUE(target.updateFrom(&expected));
}

void test_update_from_updates_all(void)
{
    expected.setLed(1, true);
    expected.setLed(5, true);
    target.updateFrom(&expected);
    assert();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_first_digit_eight);
    RUN_TEST(test_first_digit_zero);
    RUN_TEST(test_first_digit_one);
    RUN_TEST(test_second_digit_three);
    RUN_TEST(test_part_no_leading_zero);
    RUN_TEST(test_part_with_leading_zero);
    RUN_TEST(test_update_from_returns_false_if_no_update_required);
    RUN_TEST(test_update_from_returns_true_if_update_required);
    RUN_TEST(test_update_from_updates_all);
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