#include "smol/filesystem.h"
#include <unistd.h>
#include <sys/stat.h>

namespace smol::filesystem
{
auto create_directory(const path &p_path, std::error_code &p_ec) noexcept -> bool
{
    if (mkdir(p_path.native().c_str(), 0777) == -1) {
        p_ec = std::make_error_code(static_cast<std::errc>(errno));
        return false;
    }
    p_ec.clear();
    return true;
}

auto current_path() -> path
{
    std::array<char, 80 + 1> cwd;
    if (getcwd(cwd.data(), cwd.size()) == nullptr)
        return {};
    return path{cwd.data()};
}

auto current_path(const path &p_path, std::error_code &p_ec) -> void
{
    if (chdir(p_path.native().c_str()) == -1) {
        p_ec = std::make_error_code(static_cast<std::errc>(errno));
        return;
    }
    p_ec.clear();
}

auto remove(const path &p_path, std::error_code &p_ec) noexcept -> bool
{
    auto path_str = p_path.native().c_str();

    // if (p_path.is_directory()) {
        if (rmdir(path_str) == -1) {
            p_ec = std::make_error_code(static_cast<std::errc>(errno));
            return false;
        }
    // } else {
        if (unlink(path_str) == -1) {
            p_ec = std::make_error_code(static_cast<std::errc>(errno));
            return false;
        }
    // }


    p_ec.clear();
    return true;
}

} // namespace smol::filesystem
