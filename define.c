#include <stdio.h>
#define TESTS \
    TEST(num1, a) \
    TEST(num2, b) \
    TEST(num3, c)
enum test_enum{
#define TEST(NAME, OUT) Input_##NAME,
    TESTS
#undef TEST
};

int main(int argc, char const *argv[])
{
    enum test_enum test = Input_num1;
    return 0;
}

