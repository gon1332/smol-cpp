#pragma once

#include "smol_string.h"
#include <string_view>

namespace smol::filesystem
{
class path
{
public:
    using value_type = char;
    using string_type = smol::string<40>;

    static constexpr value_type preferred_separator{'/'};

    path() noexcept = default;
    explicit path(string_type &&p_str);
    explicit path(const value_type *p_str);
    template <class Source>
    explicit path(const Source &p_source);
    template <class InputIt>
    explicit path(InputIt p_first, InputIt p_last);

    /// Concatenation
    auto operator/=(const path &p_path) -> path &;
    template <class Source>
    auto operator/=(const Source &p_source) -> path &;
    template <class Source>
    auto append(const Source &p_source) -> path &;

    auto operator+=(const path &p_path) -> path &;
    auto operator+=(const string_type &p_str) -> path &;
    auto operator+=(std::string_view p_str) -> path &;
    auto operator+=(const value_type *p_str) -> path &;
    auto operator+=(value_type p_val) -> path &;
    template <class Source>
    auto operator+=(const Source &p_source) -> path &;
    template <class Source>
    auto concat(const Source &p_source) -> path &;

    /// Format Observers
    auto native() const noexcept -> const string_type &;

    [[nodiscard]] auto empty() const noexcept -> bool;
    [[nodiscard]] auto has_root_directory() const noexcept -> bool;
    [[nodiscard]] auto has_filename() const noexcept -> bool;
    [[nodiscard]] auto is_absolute() const noexcept -> bool;
    [[nodiscard]] auto is_relative() const noexcept -> bool;

    friend bool operator==(const path &p_lhs, const path &p_rhs) noexcept;
    friend bool operator!=(const path &p_lhs, const path &p_rhs) noexcept;
    template <class OStream>
    friend auto operator<<(OStream &p_os, const path &p_path) -> OStream &;

private:
    string_type m_path;
};

path::path(string_type &&p_str) : path{p_str} {}

path::path(const value_type *p_str) : m_path{p_str} {}

template <class Source>
path::path(const Source &p_source) : m_path{p_source} {}

template <class InputIt>
path::path(InputIt p_first, InputIt p_last) : m_path{string_type{p_first, p_last}} {}

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

template <class Source>
auto path::operator/=(const Source &p_source) -> path &
{
    return operator/=(path(p_source));
}

template <class Source>
auto path::append(const Source &p_source) -> path &
{
    return operator/=(p_source);
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

auto path::operator+=(std::string_view p_str) -> path &
{
    m_path += string_type{p_str.begin(), p_str.end()};
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

template <class Source>
auto path::operator+=(const Source &p_source) -> path &
{
    return operator+=(p_source);
}

template <class Source>
auto path::concat(const Source &p_source) -> path &
{
    return operator+=(p_source);
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

template <class OStream>
auto operator<<(OStream &p_os, const path &p_path) -> OStream &
{
    p_os << "\"" << p_path.native() << "\"";
    return p_os;
}
} // namespace smol
