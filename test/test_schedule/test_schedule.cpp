#include <unity.h>
#include "Schedule.h"

Schedule<byte> target(10, 1);
Schedule<bool> targetBool(false, 1);

void setUp(void)
{
    target.reset();
    targetBool.reset();
}

void tearDown(void) {}

void test_initializes(void)
{
    for (byte i = 0; i < HOURS_IN_DAY; i++)
    {
        TEST_ASSERT_EQUAL(10, target.valueFor(i));
    }
}

void test_setup_range(void)
{
    target.setup(5, 6, 12);
    for (byte i = 0; i < HOURS_IN_DAY; i++)
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

void test_update_single_value(void)
{
    target.update(1141);
    TEST_ASSERT_EQUAL(1, target.valueFor(14));
}

void test_does_not_update_single_value(void)
{
    bool actual = target.update(5141);
    TEST_ASSERT_EQUAL(10, target.valueFor(14));
    TEST_ASSERT_FALSE(actual);
}

void test_update_single_bool_value(void)
{
    targetBool.update(1141);
    TEST_ASSERT_EQUAL(true, targetBool.valueFor(14));
}

void test_does_not_update_invalid_hour(void)
{
    bool actual = target.update(1241);

    TEST_ASSERT_FALSE(actual);
}

void test_updates_only_specified_first_quarter(void)
{
    bool actual = target.update(114012);

    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 14));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 29));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 44));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 59));
}

void test_updates_only_specified_second_quarter(void)
{
    bool actual = target.update(114022);

    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 14));
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 29));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 44));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 59));
}

void test_updates_only_specified_third_quarter(void)
{
    bool actual = target.update(114042);

    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 14));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 29));
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 44));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 59));
}

void test_updates_only_specified_last_quarter(void)
{
    bool actual = target.update(114082);

    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 14));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 29));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 44));
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 59));
}

void test_updates_only_specified_first_half(void)
{
    bool actual = target.update(114032);

    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 14));
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 29));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 44));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 59));
}

void test_updates_only_specified_last_half(void)
{
    bool actual = target.update(114122);

    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 14));
    TEST_ASSERT_EQUAL(10, target.valueFor(14, 29));
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 44));
    TEST_ASSERT_EQUAL(2, target.valueFor(14, 59));
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_initializes);
    RUN_TEST(test_setup_range);
    RUN_TEST(test_update_single_value);
    RUN_TEST(test_does_not_update_single_value);
    RUN_TEST(test_update_single_bool_value);
    RUN_TEST(test_does_not_update_invalid_hour);
    RUN_TEST(test_updates_only_specified_first_quarter);
    RUN_TEST(test_updates_only_specified_second_quarter);
    RUN_TEST(test_updates_only_specified_third_quarter);
    RUN_TEST(test_updates_only_specified_last_quarter);
    RUN_TEST(test_updates_only_specified_first_half);
    RUN_TEST(test_updates_only_specified_last_half);
    UNITY_END();

    return 0;
}