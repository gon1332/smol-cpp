#include <gtest/gtest.h>
#include <string_view>
#include "small_string.h"

using namespace gon;

TEST(small_string, create)
{
    {
        small_string<5> s;
        EXPECT_TRUE(s.empty());
        EXPECT_EQ(0, s.length());
        EXPECT_EQ(0, s.size());
        EXPECT_STREQ("", s.c_str());
    }
    {
        small_string<20> s{"sorry miss jackson"};
        EXPECT_FALSE(s.empty());
        EXPECT_EQ(18, s.length());
        EXPECT_EQ(18, s.size());
        EXPECT_STREQ("sorry miss jackson", s.c_str());
    }
    {
        small_string<5> s{"a"};
        small_string<5> c{s};
        EXPECT_FALSE(c.empty());
        EXPECT_EQ(1, c.length());
        EXPECT_EQ(1, s.size());
        EXPECT_STREQ("a", c.c_str());
    }
}

TEST(small_string, assign)
{
    small_string<5> s{"abc"};
    small_string<5> s2{"xyz"};
    s = s2;
    EXPECT_EQ("xyz", s);
    s = "klm";
    EXPECT_EQ("klm", s);
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
    {
        small_string<5> s;
        small_string<2> s1{"ab"};
        small_string<4> s2{"cdef"};
        s += s1;
        EXPECT_EQ("ab", s);
        s += s2;
        EXPECT_EQ(5, s.length());
        EXPECT_EQ("abcde", s);
    }
}

TEST(small_string, compare)
{
    small_string<5> s1{"abc"};
    small_string<6> s2{"abc"};
    std::string_view sv{"abc"};
    EXPECT_EQ(s1, s2);
    EXPECT_EQ(s2, s1);
    EXPECT_EQ(s1, "abc");
    EXPECT_EQ("abc", s1);
    EXPECT_EQ(s1, sv);
    EXPECT_EQ(sv, s1);

    small_string<5> s3{"ab"};
    EXPECT_NE(s1, s3);
    EXPECT_NE(s3, s1);
    EXPECT_NE(s1, "ab");
    EXPECT_NE("ab", s1);
    std::string_view sv2{"a"};
    EXPECT_NE(s1, sv2);
    EXPECT_NE(sv2, s1);
}

TEST(small_string, element_access)
{
    small_string<5> s{"abcde"};
    EXPECT_EQ('a', *s.begin());
    EXPECT_EQ('a', s[0]);
    EXPECT_EQ('b', s[1]);
    EXPECT_EQ('c', s[2]);
    EXPECT_EQ('d', s[3]);
    EXPECT_EQ('e', s[4]);
    EXPECT_EQ('a', s.front());
    EXPECT_EQ('e', s.back());

    s.front() = 'e';
    EXPECT_EQ('e', s.front());
    s.back() = 'a';
    EXPECT_EQ('a', s.back());
}
