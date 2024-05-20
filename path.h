#pragma once

#include "small_string.h"

namespace gon::filesystem
{
class path
{
public:
    using value_type = char;
    using string_type = gon::small_string<40>;

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

template <class Source>
path::path(const Source &source) : m_path{source} {}

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

template <class OStream>
auto operator<<(OStream &os, const path &p) -> OStream &
{
    os << "\"" << p.native() << "\"";
    return os;
}
} // namespace gon
