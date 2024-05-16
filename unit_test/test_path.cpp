#include <gtest/gtest.h>
#include "path.h"

namespace fs = gon::filesystem;

TEST(path, create)
{
    {
        fs::path p;
        EXPECT_TRUE(p.empty());
    }
    {
        fs::path p{"."};
        EXPECT_FALSE(p.empty());
        EXPECT_TRUE(p.has_filename());
        EXPECT_FALSE(p.is_absolute());
        EXPECT_TRUE(p.is_relative());
    }
    {
        fs::path p{"/"};
        EXPECT_FALSE(p.empty());
        EXPECT_FALSE(p.has_filename());
        EXPECT_TRUE(p.is_absolute());
        EXPECT_FALSE(p.is_relative());
    }
    {
        fs::path p{"/mnt"};
        EXPECT_FALSE(p.empty());
        EXPECT_TRUE(p.has_filename());
        EXPECT_TRUE(p.is_absolute());
        EXPECT_FALSE(p.is_relative());

        fs::path p2{p};
        EXPECT_FALSE(p.empty());
        EXPECT_FALSE(p2.empty());
        EXPECT_TRUE(p2.has_filename());
        EXPECT_TRUE(p2.is_absolute());
        EXPECT_FALSE(p2.is_relative());
    }
}

TEST(path, append)
{
    {
        fs::path p;
        EXPECT_TRUE(p.empty());
        auto p2 = p.append("/");
        EXPECT_EQ(p, p2);
        EXPECT_EQ(p, fs::path("/"));

        p.append("a");
        EXPECT_EQ(p, fs::path("/a"));
        p.append("b");
        EXPECT_EQ(p, fs::path("/a/b"));
        p.append("/c");
        EXPECT_EQ(p, fs::path("/c"));
    }
    {
        fs::path p;
        p.append(fs::path("/"));
        EXPECT_EQ(p, fs::path("/"));
        p /= fs::path("a");
        EXPECT_EQ(p, fs::path("/a"));
        p /= fs::path("b");
        EXPECT_EQ(p, fs::path("/a/b"));
        p /= fs::path("");
        EXPECT_EQ(p, fs::path("/a/b/"));
    }
}

TEST(path, concat)
{
    fs::path p;
    p.concat("/");
    EXPECT_EQ(p, fs::path("/"));
    p.concat(fs::path("/"));
    EXPECT_EQ(p, fs::path("//"));
    p += "a";
    EXPECT_EQ(p, fs::path("//a"));
    p += ".txt";
    EXPECT_EQ(p, fs::path("//a.txt"));
}
