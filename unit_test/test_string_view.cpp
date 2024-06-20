#include <gtest/gtest.h>
#include <sstream>
#include <string_view>
#include "smol/string_view.h"

TEST(string_vew, create)
{
    {
        smol::string_view str;
        EXPECT_TRUE(str.empty());
        EXPECT_EQ(0, str.length());
        EXPECT_EQ(0, str.size());
        EXPECT_EQ(nullptr, str.data());
    }
    {
        smol::string_view str{"abc"};
        EXPECT_FALSE(str.empty());
        EXPECT_EQ(3, str.length());
        EXPECT_EQ(3, str.size());
        EXPECT_EQ('a', *str.data());
        EXPECT_EQ('a', str.front());
        EXPECT_EQ('c', str.back());

        smol::string_view str2{str};
        EXPECT_FALSE(str.empty());
        EXPECT_EQ(3, str.length());
        EXPECT_EQ(3, str.size());
        EXPECT_EQ('a', *str.data());
        EXPECT_EQ('a', str.front());
        EXPECT_EQ('a', *str.begin());
        EXPECT_EQ('c', str.back());
        EXPECT_EQ('c', *(str.end() - 1));
    }
    {
        smol::string_view str{"abcde", 3};
        EXPECT_FALSE(str.empty());
        EXPECT_EQ(3, str.length());
        EXPECT_EQ(3, str.size());
        EXPECT_EQ('a', *str.data());
        EXPECT_EQ('a', str.front());
        EXPECT_EQ('a', *str.begin());
        EXPECT_EQ('c', str.back());
        EXPECT_EQ('c', *(str.end() - 1));
    }
}

TEST(string_view, assign)
{
    smol::string_view str{"abc"};
    smol::string_view str2{"xyz"};
    str = str2;
    EXPECT_EQ("xyz", str);
    str = "klm";
    EXPECT_EQ("klm", str);
}

TEST(string_view, compare)
{
    smol::string_view str1{"abc"};
    smol::string_view str2{"abc"};
    EXPECT_EQ(str1, str2);
    EXPECT_EQ(str2, str1);
    EXPECT_EQ(str1, "abc");
    EXPECT_EQ("abc", str1);

    smol::string_view str3{"ab"};
    EXPECT_NE(str1, str3);
    EXPECT_NE(str3, str1);
    EXPECT_NE(str1, "ab");
    EXPECT_NE("ab", str1);
}

TEST(string_view, element_access)
{
    smol::string_view str{"abcde"};
    EXPECT_EQ('a', *str.begin());
    EXPECT_EQ('a', str[0]);
    EXPECT_EQ('b', str[1]);
    EXPECT_EQ('c', str[2]);
    EXPECT_EQ('d', str[3]);
    EXPECT_EQ('e', str[4]);
    EXPECT_EQ('a', str.front());
    EXPECT_EQ('e', str.back());
}

TEST(string_view, stream)
{
    smol::string_view str{"abcde"};
    std::stringstream out;
    out << str;
    EXPECT_EQ("abcde", out.str());
}
