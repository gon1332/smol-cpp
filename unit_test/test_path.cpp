#include <gtest/gtest.h>
#include <sstream>
#include "smol/smol.h"
#include "smol/filesystem.h"

namespace fs = smol::filesystem;

TEST(path, create)
{
    {
        fs::path path;
        EXPECT_TRUE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_FALSE(path.has_root_directory());
        EXPECT_FALSE(path.is_absolute());
        EXPECT_TRUE(path.is_relative());
        EXPECT_EQ(path, fs::path(""));
    }
    {
        fs::path path{""};
        EXPECT_TRUE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_FALSE(path.has_root_directory());
        EXPECT_FALSE(path.is_absolute());
        EXPECT_TRUE(path.is_relative());
        EXPECT_EQ(path, fs::path(""));
    }
    {
        fs::path path{"."};
        EXPECT_FALSE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_FALSE(path.has_root_directory());
        EXPECT_FALSE(path.is_absolute());
        EXPECT_TRUE(path.is_relative());
        EXPECT_EQ(path, fs::path("."));
    }
    {
        fs::path path{"/"};
        EXPECT_FALSE(path.empty());
        EXPECT_FALSE(path.has_filename());
        EXPECT_TRUE(path.has_root_directory());
        EXPECT_TRUE(path.is_absolute());
        EXPECT_FALSE(path.is_relative());
        EXPECT_EQ(path, fs::path("/"));
    }
    {
        fs::path path{"a/b/c"};
        EXPECT_FALSE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_FALSE(path.has_root_directory());
        EXPECT_FALSE(path.is_absolute());
        EXPECT_TRUE(path.is_relative());
        EXPECT_EQ(path, fs::path("a/b/c"));
    }
    {
        fs::path::string_type str{"/mnt"};
        auto &&str_rval{str};
        fs::path path{str_rval};
        EXPECT_FALSE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_TRUE(path.has_root_directory());
        EXPECT_TRUE(path.is_absolute());
        EXPECT_FALSE(path.is_relative());
        EXPECT_EQ(path, fs::path("/mnt"));
    }
    {
        STD_OR_SMOL::string_view path_view{"/mnt"};
        fs::path path{path_view.begin(), path_view.end()};
        EXPECT_FALSE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_TRUE(path.has_root_directory());
        EXPECT_TRUE(path.is_absolute());
        EXPECT_FALSE(path.is_relative());
        EXPECT_EQ(path, fs::path("/mnt"));
    }
    {
        fs::path path{"/mnt"};
        EXPECT_FALSE(path.empty());
        EXPECT_TRUE(path.has_filename());
        EXPECT_TRUE(path.has_root_directory());
        EXPECT_TRUE(path.is_absolute());
        EXPECT_FALSE(path.is_relative());
        EXPECT_EQ(path, fs::path("/mnt"));

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
    path += fs::path::string_type("b");
    EXPECT_EQ(path, fs::path("//ab"));
    path += STD_OR_SMOL::string_view("/");
    EXPECT_EQ(path, fs::path("//ab/"));
    path += 'c';
    EXPECT_EQ(path, fs::path("//ab/c"));
    path += ".txt";
    EXPECT_EQ(path, fs::path("//ab/c.txt"));
}

TEST(path, lexically_normal)
{
    EXPECT_EQ("", fs::path("").lexically_normal().native());
    EXPECT_EQ("/", fs::path("/").lexically_normal().native());
    EXPECT_EQ("/a/b/c", fs::path("/a/b/c").lexically_normal().native());
    EXPECT_EQ("/a/b/c", fs::path("//a//b//c").lexically_normal().native());
    EXPECT_EQ("/", fs::path("//").lexically_normal().native());
    EXPECT_EQ("/", fs::path("///").lexically_normal().native());
    EXPECT_EQ("/", fs::path("/.").lexically_normal().native());
    EXPECT_EQ("/", fs::path("/././").lexically_normal().native());
    EXPECT_EQ("/", fs::path("/a/..").lexically_normal().native());
    EXPECT_EQ(".", fs::path("./").lexically_normal().native());
    EXPECT_EQ(".", fs::path("a/../").lexically_normal().native());
    EXPECT_EQ(".", fs::path("a/..").lexically_normal().native());
    EXPECT_EQ("a/b", fs::path("a/b").lexically_normal().native());
    EXPECT_EQ("a/", fs::path("a///").lexically_normal().native());
    EXPECT_EQ("/a/c/", fs::path("/a/b/../c/").lexically_normal().native());
}

TEST(path, equality)
{
    EXPECT_NE(fs::path("/"), fs::path("//"));
    EXPECT_EQ("a/b/c", fs::path("a/b/c").native());
    EXPECT_EQ("a/b/c/", fs::path("a/b/c/").native());
}

TEST(path, stream)
{
    std::stringstream out;
    out << fs::path{"/mnt/everest"};
    EXPECT_EQ("\"/mnt/everest\"", out.str());
}
