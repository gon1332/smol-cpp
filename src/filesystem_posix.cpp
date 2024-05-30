#include "smol/filesystem.h"
#include <unistd.h>

namespace smol::filesystem
{
auto current_path() -> path
{
    std::array<char, 80 + 1> cwd;
    auto *result = getcwd(cwd.data(), cwd.size());
    if (result == nullptr)
        return {};
    return path{cwd.data()};
}

auto current_path(const path &p_path, std::error_code &p_ec) -> void
{
    auto ret = chdir(p_path.native().c_str());
    if (ret == -1) {
        p_ec = std::make_error_code(static_cast<std::errc>(errno));
        return;
    }
    p_ec.clear();
}
} // namespace smol::filesystem
