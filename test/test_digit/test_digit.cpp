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

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_segment_zero);
    RUN_TEST(test_segment_one);
    RUN_TEST(test_segment_two);
    RUN_TEST(test_segment_range_one_two);
    RUN_TEST(test_eight);
    RUN_TEST(test_zero);
    RUN_TEST(test_one);
    RUN_TEST(test_two);
    RUN_TEST(test_four);
    RUN_TEST(test_seven);
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