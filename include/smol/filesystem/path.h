#pragma once

#include <iterator>
#include "smol/string.h"

#if defined(USE_STD_STRING_VIEW)
#include <string_view>
#define STD_OR_SMOL std
#else
#include "smol/string_view.h"
#define STD_OR_SMOL smol
#endif

namespace smol
{
namespace filesystem
{
class path
{
public:
    class iterator;

    using value_type = char;
    using string_type = smol::string<40>;

    static constexpr value_type preferred_separator{'/'};

    path() noexcept = default;
    explicit path(string_type &&p_str);
    explicit path(const value_type *p_str);
    template <class Source>
    explicit path(const Source &p_source) : m_path{p_source} {}
    template <class InputIt>
    explicit path(InputIt p_first, InputIt p_last) : m_path{string_type{p_first, p_last}} {}

    /// Concatenation
    auto operator/=(const path &p_path) -> path &;
    template <class Source>
    auto operator/=(const Source &p_source) -> path & { return operator/=(path(p_source)); }
    template <class Source>
    auto append(const Source &p_source) -> path & { return operator/=(p_source); }

    auto operator+=(const path &p_path) -> path &;
    auto operator+=(const string_type &p_str) -> path &;
    auto operator+=(STD_OR_SMOL::string_view p_str) -> path &;
    auto operator+=(const value_type *p_str) -> path &;
    auto operator+=(value_type p_val) -> path &;

    template <class Source>
    auto operator+=(const Source &p_source) -> path & { return operator+=(p_source); }
    template <class Source>
    auto concat(const Source &p_source) -> path & { return operator+=(p_source); }

    /// Format Observers
    auto native() const noexcept -> const string_type &;

    auto lexically_normal() const -> path;

    [[nodiscard]] auto empty() const noexcept -> bool;
    [[nodiscard]] auto has_root_directory() const noexcept -> bool;
    [[nodiscard]] auto has_filename() const noexcept -> bool;
    [[nodiscard]] auto is_absolute() const noexcept -> bool;
    [[nodiscard]] auto is_relative() const noexcept -> bool;

    auto begin() const -> iterator;
    auto end() const -> iterator;

    friend bool operator==(const path &p_lhs, const path &p_rhs) noexcept
    {
        return p_lhs.m_path == p_rhs.m_path;
    }

    friend bool operator!=(const path &p_lhs, const path &p_rhs) noexcept
    {
        return !(p_lhs == p_rhs);
    }

    template <class OStream>
    friend auto operator<<(OStream &p_os, const path &p_path) -> OStream &
    {
        p_os << "\"" << p_path.native() << "\"";
        return p_os;
    }

private:
    string_type m_path;
};
} // namespace filesystem
} // namespace smol
