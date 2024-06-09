#pragma once

#include "filesystem/path.h"
#include <bitset>
#include <system_error>

namespace smol::filesystem
{
enum class file_type
{
    none,
    not_found,
    regular,
    directory,
    symlink,
    block,
    character,
    fifo,
    socket,
    unknown,
};

enum class perms : unsigned
{
    none = 0,
    owner_read = 0400,
    owner_write = 0200,
    owner_exec = 0100,
    owner_all = 0700,

    group_read = 040,
    group_write = 020,
    group_exec = 010,
    group_all = 070,

    others_read = 04,
    others_write = 02,
    others_exec = 01,
    others_all = 07,

    all = 0777,

    set_uid = 04000,
    set_gid = 02000,
    sticky_bit = 01000,
    mask = 07777,

    unknown = 0xFFFF,
};

constexpr auto operator&(perms p_lhs, perms p_rhs) noexcept -> perms
{
    return static_cast<perms>(
        static_cast<std::underlying_type<perms>::type>(p_lhs) &
        static_cast<std::underlying_type<perms>::type>(p_rhs));
}

constexpr auto operator&(std::underlying_type<perms>::type p_lhs, perms p_rhs) noexcept -> perms
{
    return static_cast<perms>(
        p_lhs &
        static_cast<std::underlying_type<perms>::type>(p_rhs));
}

constexpr auto operator|(perms p_lhs, perms p_rhs) noexcept -> perms
{
    return static_cast<perms>(
        static_cast<std::underlying_type<perms>::type>(p_lhs) |
        static_cast<std::underlying_type<perms>::type>(p_rhs));
}

constexpr auto operator^(perms p_lhs, perms p_rhs) noexcept -> perms
{
    return static_cast<perms>(
        static_cast<std::underlying_type<perms>::type>(p_lhs) ^
        static_cast<std::underlying_type<perms>::type>(p_rhs));
}

class file_status
{
public:
    file_status() noexcept : file_status{file_type::none} {}
    explicit file_status(file_type p_type, perms p_perms = perms::unknown) noexcept
        : m_type{p_type}, m_perms{p_perms}
    {
    }

    auto type() const noexcept -> file_type { return m_type; }
    auto type(file_type p_type) noexcept -> void { m_type = p_type; }
    auto permissions() const noexcept -> perms { return m_perms; }
    auto permissions(perms p_perms) noexcept -> void { m_perms = p_perms; }

private:
    file_type m_type;
    perms m_perms;
};

auto create_directory(const path &p_path, std::error_code &p_ec) noexcept -> bool;
auto current_path() -> path;
auto current_path(const path &p_path, std::error_code &p_ec) -> void;
auto remove(const path &p_path, std::error_code &p_ec) noexcept -> bool;
auto remove_all(const path &p_path, std::error_code &p_ec) noexcept -> std::uintmax_t;
auto status(const path &p_path, std::error_code &p_ec) noexcept -> file_status;

auto is_directory(file_status p_status) noexcept -> bool;
auto is_directory(const path &p_path, std::error_code& p_ec) noexcept -> bool;
} // namespace filesystem
