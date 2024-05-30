#include <gtest/gtest.h>
#include <system_error>
#include "smol/filesystem.h"

namespace fs = smol::filesystem;

TEST(filesystem, current_path)
{
    std::error_code ec;
    fs::current_path(fs::path{"/tmp"}, ec);
    ASSERT_FALSE(ec);
    EXPECT_EQ(fs::path{"/tmp"}, fs::current_path());
}
