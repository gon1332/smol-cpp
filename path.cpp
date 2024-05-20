#include "path.h"
#include <string_view>

namespace gon::filesystem
{
path::path(string_type &&p_str) : m_path{p_str} {}

path::path(const value_type *p_str) : m_path{p_str} {}

auto path::operator/=(const path &p_path) -> path &
{
    if (p_path.is_absolute()) {
        m_path = p_path.native();
        return *this;
    }

    if (has_filename())
        m_path += preferred_separator;

    m_path += p_path.native();
    return *this;
}

auto path::operator+=(const path &p_path) -> path &
{
    m_path += p_path.native();
    return *this;
}

auto path::operator+=(const string_type &p_str) -> path &
{
    m_path += p_str;
    return *this;
}

auto path::operator+=(const value_type *p_str) -> path &
{
    m_path += p_str;
    return *this;
}

auto path::operator+=(value_type p_val) -> path &
{
    return *this += std::string_view(&p_val, 1);
}

auto path::native() const noexcept -> const string_type & { return m_path; }

auto path::empty() const noexcept -> bool { return m_path.empty(); }

auto path::has_root_directory() const noexcept -> bool
{
    return !m_path.empty() && m_path.front() == preferred_separator;
}

auto path::has_filename() const noexcept -> bool
{
    return m_path.empty() || m_path.back() != preferred_separator;
}

auto path::is_absolute() const noexcept -> bool
{
    return has_root_directory();
}

auto path::is_relative() const noexcept -> bool
{
    return !is_absolute();
}

bool operator==(const path &p_lhs, const path &p_rhs) noexcept
{
    return p_lhs.m_path == p_rhs.m_path;
}

bool operator!=(const path &p_lhs, const path &p_rhs) noexcept
{
    return !(p_lhs == p_rhs);
}
} // namespace gon
