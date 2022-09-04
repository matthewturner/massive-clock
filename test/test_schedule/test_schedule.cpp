#include <unity.h>
#include "Schedule.h"

Schedule<byte> target(10);

void setUp(void)
{
    target.reset();
}

void tearDown(void) {}

void test_initializes(void)
{
    for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
    {
        TEST_ASSERT_EQUAL(10, target.valueFor(i));
    }
}

void test_setup_range(void)
{
    target.setup(5, 6, 12);
    for (byte i = 0; i < SEGMENTS_IN_DAY; i++)
    {
        if (i == 5 || i == 6)
        {
            TEST_ASSERT_EQUAL(12, target.valueFor(i));
        }
        else
        {
            TEST_ASSERT_EQUAL(10, target.valueFor(i));
        }
    }
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_initializes);
    RUN_TEST(test_setup_range);
    UNITY_END();

    return 0;
}