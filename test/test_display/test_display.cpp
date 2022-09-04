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

void tearDown(void) {}

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
    target.setPart(0, 8, Flags::NONE);
    assert();
}

void test_part_with_leading_zero(void)
{
    expected.setLedRange(0, 41, true);
    expected.setLedRange(30, 32, false);
    target.setPart(0, 8, Flags::LEADING_ZERO);
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

void test_update_from_updates_color(void)
{
    expected.setColor(33);
    TEST_ASSERT_TRUE(target.updateFrom(&expected));
    assert();
}

void test_update_from_updates_brightness(void)
{
    expected.setBrightness(44);
    TEST_ASSERT_TRUE(target.updateFrom(&expected));
    assert();
}

void test_set_part_max(void)
{
    expected.setLedRange(0, 41, true);
    target.setPart(0, 88, Flags::NONE);
    assert();
}

void test_set_all_parts_max(void)
{
    expected.setLedRange(0, 41, true);
    expected.setLedRange(44, 85, true);
    target.setPart(0, 88, Flags::NONE);
    target.setPart(1, 88, Flags::NONE);
    assert();
}

void test_set_all_parts_max_with_separator(void)
{
    expected.setLedRange(0, 85, true);
    target.setPart(0, 88, Flags::NONE);
    target.setPart(1, 88, Flags::NONE);
    target.setSeparator(true);
    assert();
}

void test_set_text(void)
{
    expected.setDigit(4, 'r');
    expected.setDigit(3, 'e');
    expected.setDigit(1, 's');
    expected.setDigit(0, 't');
    target.setText("rest");
    assert();
}

void test_set_three_in_minimal_mode(void)
{
    expected.setLedRange(15, 17, true);
    target.setPart(0, 3, Flags::MINIMAL);
    assert();
}

void test_set_thirty_three_in_minimal_mode(void)
{
    expected.setLedRange(15, 17, true);
    expected.setLedRange(36, 38, true);
    target.setPart(0, 33, Flags::MINIMAL);
    assert();
}

void test_flags_multiple(void)
{
    Flags f = (Flags)(Flags::MINIMAL | Flags::LEADING_ZERO);
    TEST_ASSERT_TRUE((f & Flags::MINIMAL) == Flags::MINIMAL);
    TEST_ASSERT_TRUE((f & Flags::LEADING_ZERO) == Flags::LEADING_ZERO);
}

void test_flags_single(void)
{
    Flags f = (Flags)(Flags::MINIMAL);
    TEST_ASSERT_TRUE((f & Flags::MINIMAL) == Flags::MINIMAL);
    TEST_ASSERT_FALSE((f & Flags::LEADING_ZERO) == Flags::LEADING_ZERO);
}

void test_super_minimal_mode_includes_tens(void)
{
    expected.setLedRange(36, 38, true);
    target.setPart(0, 33, Flags::SUPER_MINIMAL);
    assert();
}

void test_super_minimal_mode_excludes_units(void)
{
    target.setPart(0, 6, Flags::SUPER_MINIMAL);
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
    RUN_TEST(test_update_from_updates_color);
    RUN_TEST(test_update_from_updates_brightness);
    RUN_TEST(test_set_part_max);
    RUN_TEST(test_set_all_parts_max);
    RUN_TEST(test_set_all_parts_max_with_separator);
    RUN_TEST(test_set_text);
    RUN_TEST(test_set_three_in_minimal_mode);
    RUN_TEST(test_flags_multiple);
    RUN_TEST(test_flags_single);
    RUN_TEST(test_set_thirty_three_in_minimal_mode);
    RUN_TEST(test_super_minimal_mode_includes_tens);
    RUN_TEST(test_super_minimal_mode_excludes_units);
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