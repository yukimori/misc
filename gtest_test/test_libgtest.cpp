#include <gtest/gtest.h>

TEST(MathTest, OnePlusOneIsTwo) {
    EXPECT_EQ(2, 1+1);
}

GTEST_API_ int main(int argc, char **argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
