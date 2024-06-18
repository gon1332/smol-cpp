#include <gtest/gtest.h>
#include <system_error>
#include "smol/filesystem.h"

// NOLINTBEGIN - do-while is used in a well known pattern here
#define ASSERT_NO_ERR(test, errc) \
do { \
    EXPECT_TRUE(test); \
    if (!test) { \
        std::cout << "   Error: " << errc.message() << std::endl; \
        ASSERT_FALSE(errc); \
    } \
} while (0)
// NOLINTEND

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

TEST(filesystem, directories_and_files)
{
    GTEST_SKIP();
    std::error_code errc;
    ASSERT_TRUE(fs::is_directory(fs::path{"/tmp"}, errc));
    auto num_dirs_removed = fs::remove_all(fs::path{"/tmp/sandbox"}, errc);
    ASSERT_FALSE(errc);
    ASSERT_NE(static_cast<uintmax_t>(-1), num_dirs_removed);
    ASSERT_NO_ERR(fs::create_directory(fs::path{"/tmp"}, errc), errc);
    ASSERT_NO_ERR(fs::create_directory(fs::path{"/tmp/sandbox"}, errc), errc);
    ASSERT_NO_ERR(fs::create_directory(fs::path{"/tmp/sandbox/a"}, errc), errc);
    ASSERT_NO_ERR(fs::remove(fs::path{"/tmp/sandbox/a"}, errc), errc);
    ASSERT_NO_ERR(fs::create_directory(fs::path{"/tmp/sandbox/b"}, errc), errc);
    ASSERT_NO_ERR(fs::create_directory(fs::path{"/tmp/sandbox/x/c"}, errc), errc);
}

TEST(filesystem, current_path)
{
    std::error_code errc;
    fs::current_path(fs::path{"/tmp"}, errc);
    ASSERT_FALSE(errc);
    EXPECT_EQ(fs::path{"/tmp"}, fs::current_path());
}
