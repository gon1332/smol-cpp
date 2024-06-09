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

TEST(filesystem, file_status)
{
    // First make sure the bit-ops are correct for the file permissions
    EXPECT_EQ(fs::perms::all, fs::perms::owner_all | fs::perms::group_all | fs::perms::others_all);
    EXPECT_EQ(fs::perms::none, fs::perms::owner_all & fs::perms::group_all & fs::perms::others_all);
    EXPECT_EQ(fs::perms::none, fs::perms::all ^ fs::perms::all);

    fs::file_status file_s{};
    EXPECT_EQ(fs::file_type::none, file_s.type());
    EXPECT_EQ(fs::perms::unknown, file_s.permissions());

    file_s.type(fs::file_type::directory);
    EXPECT_EQ(fs::file_type::directory, file_s.type());

    file_s.permissions(fs::perms::owner_all);
    EXPECT_EQ(fs::perms::owner_all, file_s.permissions());

}

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

// TEST(filesystem, file_types)
// {
    // std::error_code errc;
    // EXPECT_TRUE(is_directory(fs::path{"/tmp/"}, errc));
    // EXPECT_FALSE(is_directory(fs::path{"/tmp/"}, errc));
// }

TEST(filesystem, current_path)
{
    std::error_code errc;
    fs::current_path(fs::path{"/tmp"}, errc);
    ASSERT_FALSE(errc);
    EXPECT_EQ(fs::path{"/tmp"}, fs::current_path());
}
