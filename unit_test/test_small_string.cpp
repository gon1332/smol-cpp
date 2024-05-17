#include <gtest/gtest.h>
#include "small_string.h"

using namespace gon;

TEST(small_string, create)
{
    {
        small_string<5> s;
        EXPECT_TRUE(s.empty());
        EXPECT_EQ(0, s.length());
        EXPECT_STREQ("", s.c_str());
    }
    {
        small_string<20> s{"sorry miss jackson"};
        EXPECT_FALSE(s.empty());
        EXPECT_EQ(18, s.length());
        EXPECT_STREQ("sorry miss jackson", s.c_str());
    }
    {
        small_string<5> s{"a"};
        small_string<5> c{s};
        EXPECT_FALSE(c.empty());
        EXPECT_EQ(1, c.length());
        EXPECT_STREQ("a", c.c_str());
    }
}

TEST(small_string, append)
{
    {
        small_string<5> s;
        EXPECT_STREQ("", s.c_str());
        EXPECT_EQ(0, s.length());
        s.append("1");
        EXPECT_STREQ("1", s.c_str());
        EXPECT_EQ(1, s.length());
        s.append("2");
        EXPECT_STREQ("12", s.c_str());
        EXPECT_EQ(2, s.length());
        s.append("345");
        EXPECT_STREQ("12345", s.c_str());
        EXPECT_EQ(5, s.length());
        s.append("678");
        EXPECT_STREQ("12345", s.c_str());
        EXPECT_EQ(5, s.length());
    }
    {
        small_string<5> s;
        EXPECT_STREQ("", s.c_str());
        EXPECT_EQ(0, s.length());
        s += "1";
        EXPECT_STREQ("1", s.c_str());
        EXPECT_EQ(1, s.length());
        s += '2';
        EXPECT_STREQ("12", s.c_str());
        EXPECT_EQ(2, s.length());
        s += "345";
        EXPECT_STREQ("12345", s.c_str());
        EXPECT_EQ(5, s.length());
        s += "678";
        EXPECT_STREQ("12345", s.c_str());
        EXPECT_EQ(5, s.length());
    }
    {
        small_string<5> s;
        EXPECT_STREQ("", s.c_str());
        EXPECT_EQ(0, s.length());
        s.append(7, 'x');
        EXPECT_STREQ("xxxxx", s.c_str());
        EXPECT_EQ(5, s.length());
    }
}
