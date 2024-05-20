#include <gtest/gtest.h>
#include "path.h"

namespace fs = smol::filesystem;

TEST(path, create)
{
    {
        fs::path path;
        EXPECT_TRUE(path.empty());
    }
    {
        fs::path path{"."};
        EXPECT_FALSE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_FALSE(path.is_absolute());
        EXPECT_TRUE(path.is_relative());
    }
    {
        fs::path path{"/"};
        EXPECT_FALSE(path.empty());
        EXPECT_FALSE(path.has_filename());
        EXPECT_TRUE(path.is_absolute());
        EXPECT_FALSE(path.is_relative());
    }
    {
        fs::path path{"/mnt"};
        EXPECT_FALSE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_TRUE(path.is_absolute());
        EXPECT_FALSE(path.is_relative());

        fs::path path2{path};
        EXPECT_FALSE(path.empty());
        EXPECT_FALSE(path2.empty());
        EXPECT_TRUE(path2.has_filename());
        EXPECT_TRUE(path2.is_absolute());
        EXPECT_FALSE(path2.is_relative());
    }
}

TEST(path, append)
{
    {
        fs::path path;
        EXPECT_TRUE(path.empty());
        auto path2 = path.append("/");
        EXPECT_EQ(path, path2);
        EXPECT_EQ(path, fs::path("/"));

        path.append("a");
        EXPECT_EQ(path, fs::path("/a"));
        path.append("b");
        EXPECT_EQ(path, fs::path("/a/b"));
        path.append("/c");
        EXPECT_EQ(path, fs::path("/c"));
    }
    {
        fs::path path;
        path.append(fs::path("/"));
        EXPECT_EQ(path, fs::path("/"));
        path /= fs::path("a");
        EXPECT_EQ(path, fs::path("/a"));
        path /= fs::path("b");
        EXPECT_EQ(path, fs::path("/a/b"));
        path /= fs::path("");
        EXPECT_EQ(path, fs::path("/a/b/"));
    }
}

TEST(path, concat)
{
    fs::path path;
    path.concat("/");
    EXPECT_EQ(path, fs::path("/"));
    path.concat(fs::path("/"));
    EXPECT_EQ(path, fs::path("//"));
    path += "a";
    EXPECT_EQ(path, fs::path("//a"));
    path += ".txt";
    EXPECT_EQ(path, fs::path("//a.txt"));
}
