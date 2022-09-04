#include <unity.h>
#include "Schedule.h"

Schedule<byte> hourTarget(10, GRANULARITY_HOUR);
Schedule<byte> segmentTarget(10, GRANULARITY_SEGMENT);

void setUp(void)
{
    hourTarget.reset();
    segmentTarget.reset();
}

void tearDown(void) {}

void test_hour_initializes(void)
{
    for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
    {
        TEST_ASSERT_EQUAL(10, hourTarget.valueFor(i));
    }
}

void test_hour_setup_range(void)
{
    hourTarget.setup(5, 6, 12);
    for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
    {
        if (i == 5 || i == 6)
        {
            TEST_ASSERT_EQUAL(12, hourTarget.valueFor(i));
        }
        else
        {
            TEST_ASSERT_EQUAL(10, hourTarget.valueFor(i));
        }
    }
}

void test_segment_initializes(void)
{
    for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
    {
        TEST_ASSERT_EQUAL(10, segmentTarget.valueFor(i));
    }
}

void test_segment_setup_range(void)
{
    segmentTarget.setup(5, 6, 12);
    for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
    {
        if (i == 5 || i == 6)
        {
            TEST_ASSERT_EQUAL(12, segmentTarget.valueFor(i));
        }
        else
        {
            TEST_ASSERT_EQUAL(10, segmentTarget.valueFor(i));
        }
    }
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_hour_initializes);
    RUN_TEST(test_hour_setup_range);
    RUN_TEST(test_segment_initializes);
    // RUN_TEST(test_segment_setup_range);
    UNITY_END();

    return 0;
}