#include <gtest/gtest.h>
#include "smol/algorithm.h"
#include <string>

TEST(algorithm, find_first_not_of)
{
    std::string pattern{"!@#$"};
    {
        std::string text{"a!bb#"};
        auto iter = smol::find_first_not_of(text.begin(), text.end(), pattern.begin(), pattern.end());
        ASSERT_NE(iter, text.end());
        EXPECT_EQ('a', *iter);
    }
    {
        std::string text{"!$a!bb#"};
        auto iter = smol::find_first_not_of(text.begin(), text.end(), pattern.begin(), pattern.end());
        ASSERT_NE(iter, text.end());
        EXPECT_EQ('a', *iter);
    }
    {
        std::string text{"!$#"};
        auto iter = smol::find_first_not_of(text.begin(), text.end(), pattern.begin(), pattern.end());
        EXPECT_EQ(iter, text.end());
    }
    {
        std::string text;
        auto iter = smol::find_first_not_of(text.begin(), text.end(), pattern.begin(), pattern.end());
        EXPECT_EQ(iter, text.end());
    }
}
