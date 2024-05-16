#pragma once

#include <string>
#include <string_view>

namespace gon::filesystem
{
class path
{
public:
    using value_type = char;
    using string_type = std::basic_string<value_type>;

    static constexpr value_type preferred_separator{'/'};


    path() noexcept = default;
    explicit path(string_type &&source);
    template <class Source>
    explicit path(const Source &source);

    /// Concatenation
    auto operator/=(const path &source) -> path &;
    template <class Source>
    auto operator/=(const Source &source) -> path &;
    template <class Source>
    auto append(const Source &source) -> path &;

    auto operator+=(const path &p) -> path &;
    auto operator+=(const string_type &str) -> path &;
    auto operator+=(const value_type *ptr) -> path &;
    auto operator+=(value_type x) -> path &;
    template <class Source>
    auto operator+=(const Source &source) -> path &;
    template <class Source>
    auto concat(const Source &source) -> path &;

    /// Format Observers
    auto native() const noexcept -> const string_type &;

    [[nodiscard]] auto empty() const noexcept -> bool;
    [[nodiscard]] auto has_root_directory() const noexcept -> bool;
    [[nodiscard]] auto has_filename() const noexcept -> bool;
    [[nodiscard]] auto is_absolute() const noexcept -> bool;
    [[nodiscard]] auto is_relative() const noexcept -> bool;

    friend bool operator==(const path &lhs, const path &rhs) noexcept;
    friend bool operator!=(const path &lhs, const path &rhs) noexcept;
    template <class OStream>
    friend auto operator<<(OStream &os, const path &p) -> OStream &;

private:
    string_type m_path;
};

path::path(string_type &&source) : path(source) {}

template <class Source>
path::path(const Source &source) : m_path{source} {}

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

template <class Source>
auto path::operator/=(const Source &source) -> path &
{
    return operator/=(path(source));
}

template <class Source>
auto path::append(const Source &source) -> path &
{
    return operator/=(path(source));
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

template <class Source>
auto path::operator+=(const Source &source) -> path &
{
    return operator+=(path(source));
}

template <class Source>
auto path::concat(const Source &source) -> path &
{
    return operator+=(path(source));
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

template <class OStream>
auto operator<<(OStream &os, const path &p) -> OStream &
{
    os << "\"" << p.native() << "\"";
    return os;
}
} // namespace gon
