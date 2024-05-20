#pragma once

#include "smol_string.h"

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

    /// Concatenation
    auto operator/=(const path &p_path) -> path &;
    template <class Source>
    auto operator/=(const Source &p_source) -> path &;
    template <class Source>
    auto append(const Source &p_source) -> path &;

    auto operator+=(const path &p_path) -> path &;
    auto operator+=(const string_type &p_str) -> path &;
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

template <class Source>
path::path(const Source &p_source) : m_path{p_source} {}

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

template <class OStream>
auto operator<<(OStream &p_os, const path &p_path) -> OStream &
{
    p_os << "\"" << p_path.native() << "\"";
    return p_os;
}
} // namespace smol
