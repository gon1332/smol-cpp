#include "path.h"
#include <string_view>

namespace gon::filesystem
{
path::path(string_type &&source) : path(source) {}

auto path::operator/=(const path &p) -> path &
{
    if (p.is_absolute()) {
        m_path = p.native();
        return *this;
    }

    if (has_filename())
        m_path += preferred_separator;

    m_path += p.native();
    return *this;
}

auto path::operator+=(const path &p) -> path &
{
    m_path += p.native();
    return *this;
}

auto path::operator+=(const string_type &str) -> path &
{
    m_path += str;
    return *this;
}

auto path::operator+=(const value_type *ptr) -> path &
{
    m_path += ptr;
    return *this;
}

auto path::operator+=(value_type x) -> path &
{
    return *this += std::string_view(&x, 1);
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

bool operator==(const path &lhs, const path &rhs) noexcept
{
    return lhs.m_path == rhs.m_path;
}

bool operator!=(const path &lhs, const path &rhs) noexcept
{
    return !(lhs == rhs);
}
} // namespace gon
