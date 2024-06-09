#include "smol/filesystem.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

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
    struct stat f_stat;
    if (stat(p_path.native().c_str(), &f_stat) == -1) {
        p_ec = std::make_error_code(static_cast<std::errc>(errno));
        return {};
    }
    auto mode = f_stat.st_mode;
    perms prms{mode & perms::mask};
    file_type ftype;

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
    else
        ftype = file_type::unknown;

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
} // namespace smol::filesystem
