#include <unity.h>
#include <stdio.h>
#include "test_digit.h"

Digit target;
Digit expected;

void setUp(void)
{
    expected.clear();
    target.clear();
}

void tearDown(void) {}

void test_segment_zero(void)
{
    expected.setLedRange(0, 2, true);
    target.setSegment(0, true);
    assert();
}

void test_segment_one(void)
{
    expected.setLedRange(3, 5, true);
    target.setSegment(1, true);
    assert();
}

void test_segment_two(void)
{
    expected.setLedRange(6, 8, true);
    target.setSegment(2, true);
    assert();
}

void test_segment_range_one_two(void)
{
    expected.setLedRange(3, 8, true);
    target.setSegmentRange(1, 2, true);
    assert();
}

void test_eight(void)
{
    expected.setSegmentRange(0, 7, true);
    target.set(8);
    assert();
}

void test_zero(void)
{
    expected.setSegmentRange(0, 2, true);
    expected.setSegmentRange(4, 13, true);
    target.set(0);
    assert();
}

void test_one(void)
{
    expected.setSegmentRange(0, 0, true);
    expected.setSegmentRange(4, 4, true);
    target.set(1);
    assert();
}

void test_two(void)
{
    expected.setSegmentRange(0, 1, true);
    expected.setSegmentRange(3, 3, true);
    expected.setSegmentRange(5, 6, true);
    target.set(2);
    assert();
}

void test_four(void)
{
    expected.setSegmentRange(0, 0, true);
    expected.setSegmentRange(2, 4, true);
    target.set(4);
    assert();
}

void test_seven(void)
{
    expected.setSegmentRange(0, 1, true);
    expected.setSegmentRange(4, 4, true);
    target.set(7);
    assert();
}

void test_s(void)
{
    expected.setSegmentRange(1, 5, true);
    target.set('s');
    assert();
}

void test_r(void)
{
    expected.setSegmentRange(3, 3, true);
    expected.setSegmentRange(6, 6, true);
    target.set('r');
    assert();
}

void test_e(void)
{
    expected.setSegmentRange(1, 3, true);
    expected.setSegmentRange(5, 6, true);
    target.set('e');
    assert();
}

void test_t(void)
{
    expected.setSegmentRange(2, 3, true);
    expected.setSegmentRange(5, 6, true);
    target.set('t');
    assert();
}

void test_c(void)
{
    expected.setSegmentRange(3, 3, true);
    expected.setSegmentRange(5, 6, true);
    target.set('c');
    assert();
}

void test_o(void)
{
    expected.setSegmentRange(3, 6, true);
    target.set('o');
    assert();
}

void test_l(void)
{
    expected.setSegmentRange(2, 2, true);
    expected.setSegmentRange(5, 6, true);
    target.set('l');
    assert();
}

void test_space(void)
{
    target.set(' ');
    assert();
}

void test_two_dots(void)
{
    expected.setLedRange(15, 16, true);
    target.setDots(2);
    assert();
}

void test_three_dots(void)
{
    expected.setSegment(5, true);
    target.setDots(3);
    assert();
}

void test_five_dots(void)
{
    expected.setSegment(5, true);
    expected.setLedRange(10, 11, true);
    target.setDots(5);
    assert();
}

void test_six_dots(void)
{
    expected.setSegment(5, true);
    expected.setSegment(3, true);
    target.setDots(6);
    assert();
}

void test_eight_dots(void)
{
    expected.setSegment(5, true);
    expected.setSegment(3, true);
    expected.setLedRange(3, 4, true);
    target.setDots(8);
    assert();
}

void test_nine_dots(void)
{
    expected.setSegment(5, true);
    expected.setSegment(3, true);
    expected.setSegment(1, true);
    target.setDots(9);
    assert();
}

void test_dots_clear_first(void)
{
    expected.setSegment(5, true);
    target.setDots(9);
    target.setDots(3);
    assert();
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_segment_zero);
    RUN_TEST(test_segment_one);
    RUN_TEST(test_segment_two);
    RUN_TEST(test_segment_range_one_two);
    RUN_TEST(test_eight);
    // RUN_TEST(test_zero);
    // RUN_TEST(test_one);
    RUN_TEST(test_two);
    RUN_TEST(test_four);
    RUN_TEST(test_seven);
    RUN_TEST(test_s);
    RUN_TEST(test_r);
    RUN_TEST(test_e);
    RUN_TEST(test_t);
    RUN_TEST(test_c);
    RUN_TEST(test_o);
    RUN_TEST(test_l);
    RUN_TEST(test_space);
    RUN_TEST(test_two_dots);
    RUN_TEST(test_three_dots);
    RUN_TEST(test_five_dots);
    RUN_TEST(test_six_dots);
    RUN_TEST(test_eight_dots);
    RUN_TEST(test_nine_dots);
    RUN_TEST(test_dots_clear_first);
    UNITY_END();

    return 0;
}

void assert()
{
    for (byte i = 0; i < LEDS_PER_DIGIT; i++)
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