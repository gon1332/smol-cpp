#include <gtest/gtest.h>
#include <system_error>
#include "smol/filesystem.h"

namespace fs = smol::filesystem;

TEST(filesystem, current_path)
{
    std::error_code errc;
    fs::current_path(fs::path{"/tmp"}, errc);
    ASSERT_FALSE(errc);
    EXPECT_EQ(fs::path{"/tmp"}, fs::current_path());
}
