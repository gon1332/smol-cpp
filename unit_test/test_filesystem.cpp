#include <gtest/gtest.h>
#include <system_error>
#include "smol/filesystem.h"

#define ASSERT_NO_ERR(test, errc) \
do { \
    EXPECT_TRUE(test); \
    if (!test) { \
        std::cout << "   Error: " << errc.message() << std::endl; \
        ASSERT_FALSE(errc); \
    } \
} while (0)

namespace fs = smol::filesystem;

TEST(filesystem, create_directories)
{
    std::error_code errc;
    ASSERT_NO_ERR(remove(fs::path{"/tmp/sandbox"}, errc), errc);
    ASSERT_NO_ERR(create_directory(fs::path{"/tmp"}, errc), errc);
    ASSERT_NO_ERR(create_directory(fs::path{"/tmp/sandbox"}, errc), errc);
    ASSERT_NO_ERR(create_directory(fs::path{"/tmp/sandbox/a"}, errc), errc);
    ASSERT_NO_ERR(remove(fs::path{"/tmp/sandbox/a"}, errc), errc);
    ASSERT_NO_ERR(create_directory(fs::path{"/tmp/sandbox/b"}, errc), errc);
    ASSERT_NO_ERR(create_directory(fs::path{"/tmp/sandbox/x/c"}, errc), errc);
}

TEST(filesystem, current_path)
{
    std::error_code errc;
    fs::current_path(fs::path{"/tmp"}, errc);
    ASSERT_FALSE(errc);
    EXPECT_EQ(fs::path{"/tmp"}, fs::current_path());
}
