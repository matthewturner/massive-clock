#include <unity.h>
#include "Brightness.h"

Brightness target;

void setUp(void)
{
    target.reset();
}

void test_first_value(void)
{
    TEST_ASSERT_EQUAL(20, target.from(20));
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_first_value);
    UNITY_END();

    return 0;
}