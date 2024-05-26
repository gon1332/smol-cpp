#include <gtest/gtest.h>
#include <sstream>
#include <string_view>
#include "smol/string.h"

TEST(string, create)
{
    {
        smol::string<5> str;
        EXPECT_TRUE(str.empty());
        EXPECT_EQ(0, str.length());
        EXPECT_EQ(0, str.size());
        EXPECT_STREQ("", str.c_str());
    }
    {
        smol::string<5> str{""};
        EXPECT_TRUE(str.empty());
        EXPECT_EQ(0, str.length());
        EXPECT_EQ(0, str.size());
        EXPECT_STREQ("", str.c_str());
    }
    {
        smol::string<20> str{"sorry miss jackson"};
        EXPECT_FALSE(str.empty());
        EXPECT_EQ(18, str.length());
        EXPECT_EQ(18, str.size());
        EXPECT_STREQ("sorry miss jackson", str.c_str());
    }
    {
        smol::string<5> str{"a"};
        smol::string<5> str2{str};
        EXPECT_FALSE(str2.empty());
        EXPECT_EQ(1, str2.length());
        EXPECT_EQ(1, str.size());
        EXPECT_STREQ("a", str2.c_str());
    }
    {
        smol::string<3> str{"abcde"};
        EXPECT_FALSE(str.empty());
        EXPECT_EQ(3, str.length());
        EXPECT_EQ(3, str.size());
        EXPECT_STREQ("abc", str.c_str());
    }
    {
        std::string_view str_v{"abcde"};
        smol::string<3> str{str_v.begin(), str_v.end()};
        EXPECT_FALSE(str.empty());
        EXPECT_EQ(3, str.length());
        EXPECT_EQ(3, str.size());
        EXPECT_STREQ("abc", str.c_str());
    }
}

TEST(string, assign)
{
    smol::string<5> str{"abc"};
    smol::string<5> str2{"xyz"};
    str = str2;
    EXPECT_EQ("xyz", str);
    str = "klm";
    EXPECT_EQ("klm", str);
}

TEST(string, append)
{
    {
        smol::string<5> str;
        EXPECT_STREQ("", str.c_str());
        EXPECT_EQ(0, str.length());
        str.append("1");
        EXPECT_STREQ("1", str.c_str());
        EXPECT_EQ(1, str.length());
        str.append("2");
        EXPECT_STREQ("12", str.c_str());
        EXPECT_EQ(2, str.length());
        str.append("345");
        EXPECT_STREQ("12345", str.c_str());
        EXPECT_EQ(5, str.length());
        str.append("678");
        EXPECT_STREQ("12345", str.c_str());
        EXPECT_EQ(5, str.length());
    }
    {
        smol::string<5> str;
        EXPECT_STREQ("", str.c_str());
        EXPECT_EQ(0, str.length());
        str += "1";
        EXPECT_STREQ("1", str.c_str());
        EXPECT_EQ(1, str.length());
        str += '2';
        EXPECT_STREQ("12", str.c_str());
        EXPECT_EQ(2, str.length());
        str += "345";
        EXPECT_STREQ("12345", str.c_str());
        EXPECT_EQ(5, str.length());
        str += "678";
        EXPECT_STREQ("12345", str.c_str());
        EXPECT_EQ(5, str.length());
    }
    {
        smol::string<5> str;
        EXPECT_STREQ("", str.c_str());
        EXPECT_EQ(0, str.length());
        str.append(7, 'x');
        EXPECT_STREQ("xxxxx", str.c_str());
        EXPECT_EQ(5, str.length());
    }
    {
        smol::string<5> str;
        smol::string<2> str1{"ab"};
        smol::string<4> str2{"cdef"};
        str += str1;
        EXPECT_EQ("ab", str);
        str += str2;
        EXPECT_EQ(5, str.length());
        EXPECT_EQ("abcde", str);
    }
}

TEST(string, compare)
{
    smol::string<5> str1{"abc"};
    smol::string<6> str2{"abc"};
    std::string_view sview{"abc"};
    EXPECT_EQ(str1, str2);
    EXPECT_EQ(str2, str1);
    EXPECT_EQ(str1, "abc");
    EXPECT_EQ("abc", str1);
    EXPECT_EQ(str1, sview);
    EXPECT_EQ(sview, str1);

    smol::string<5> str3{"ab"};
    EXPECT_NE(str1, str3);
    EXPECT_NE(str3, str1);
    EXPECT_NE(str1, "ab");
    EXPECT_NE("ab", str1);
    std::string_view sview2{"a"}; // different length
    EXPECT_NE(str1, sview2);
    EXPECT_NE(sview2, str1);
    std::string_view sview3{"ac"}; // same length
    EXPECT_NE(str1, sview3);
    EXPECT_NE(sview3, str1);
}

TEST(string, element_access)
{
    smol::string<5> str{"abcde"};
    EXPECT_EQ('a', *str.begin());
    EXPECT_EQ('a', str[0]);
    EXPECT_EQ('b', str[1]);
    EXPECT_EQ('c', str[2]);
    EXPECT_EQ('d', str[3]);
    EXPECT_EQ('e', str[4]);
    EXPECT_EQ('a', str.front());
    EXPECT_EQ('e', str.back());

    str.front() = 'e';
    EXPECT_EQ('e', str.front());
    str.back() = 'a';
    EXPECT_EQ('a', str.back());
}

TEST(string, stream)
{
    smol::string<5> str{"abcde"};
    std::stringstream out;
    out << str;
    EXPECT_EQ("abcde", out.str());
}
