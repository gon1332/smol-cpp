#include "smol/filesystem.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

namespace smol
{
namespace filesystem
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
    std::array<char, 80 + 1> cwd; // NOLINT - Does not need initialization
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

auto exists(file_status p_status) noexcept -> bool
{
    return status_known(p_status) && p_status.type() != file_type::not_found;
}

auto exists(const path &p_path, std::error_code &p_ec) noexcept -> bool
{
    return exists(status(p_path, p_ec));
}

auto remove(const path &p_path, std::error_code &p_ec) noexcept -> bool
{
    const auto *path_str = p_path.native().c_str();
    auto is_dir = is_directory(p_path, p_ec);
    if (p_ec)
        return false;

    if (is_dir) {
        if (rmdir(path_str) == -1) {
            p_ec = std::make_error_code(static_cast<std::errc>(errno));
            return false;
        }
    } else {
        if (unlink(path_str) == -1) {
            p_ec = std::make_error_code(static_cast<std::errc>(errno));
            return false;
        }
    }


    p_ec.clear();
    return true;
}

auto remove_all(const path &p_path, std::error_code &p_ec) noexcept -> std::uintmax_t
{
    std::uintmax_t files_deleted{};

    // TODO: Implement directory_iterator and recursive_directory_iterator

    // on error:
    return static_cast<std::uintmax_t>(-1);
}

auto status(const path &p_path, std::error_code &p_ec) noexcept -> file_status
{
    struct stat f_stat; // NOLINT - Does not need initialization
    if (stat(p_path.native().c_str(), &f_stat) == -1) {
        p_ec = std::make_error_code(static_cast<std::errc>(errno));
        return {};
    }
    auto mode = f_stat.st_mode;
    perms prms{mode & perms::mask};
    file_type ftype{file_type::unknown};

    if (S_ISREG(mode))
        ftype = file_type::regular;
    else if (S_ISDIR(mode))
        ftype = file_type::directory;
    else if (S_ISBLK(mode))
        ftype = file_type::block;
    else if (S_ISCHR(mode))
        ftype = file_type::character;
    else if (S_ISFIFO(mode))
        ftype = file_type::fifo;
    else if (S_ISSOCK(mode))
        ftype = file_type::socket;

    // TODO: Handle error cases, where there are no permissions to get stats

    p_ec.clear();
    return file_status{ftype, prms};
}

auto is_directory(file_status p_status) noexcept -> bool
{
    return p_status.type() == file_type::directory;
}

auto is_directory(const path &p_path, std::error_code& p_ec) noexcept -> bool
{
    return is_directory(status(p_path, p_ec));
}

auto is_regular(file_status p_status) noexcept -> bool
{
    return p_status.type() == file_type::regular;
}

auto is_regular(const path &p_path, std::error_code& p_ec) noexcept -> bool
{
    return is_regular(status(p_path, p_ec));
}

auto is_other(file_status p_status) noexcept -> bool
{
    return exists(p_status) && !is_regular(p_status) && !is_directory(p_status) && !is_symlink(p_status);
}

auto is_other(const path &p_path, std::error_code& p_ec) noexcept -> bool
{
    return is_other(status(p_path, p_ec));
}

auto is_symlink(file_status p_status) noexcept -> bool
{
    return p_status.type() == file_type::symlink;
}

auto is_symlink(const path &p_path, std::error_code& p_ec) noexcept -> bool
{
    return is_symlink(status(p_path, p_ec));
}

auto status_known(file_status p_status) noexcept -> bool
{
    return p_status.type() != file_type::unknown;
}
} // namespace filesystem
} // namespace smol
