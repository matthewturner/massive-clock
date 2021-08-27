#include <unity.h>
#include "Display.h"

Display target;

void test_first_digit_eight(void)
{
    target.setDigit(0, 8);
    for (byte i = 0; i < 8; i++)
    {
        TEST_ASSERT_TRUE(target.led(i));
    }
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_first_digit_eight);
    UNITY_END();

    return 0;
}