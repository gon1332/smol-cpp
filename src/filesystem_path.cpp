#include "smol/filesystem.h"
#include <algorithm>
#include <iterator>
#include "smol/algorithm.h"
#include "smol/string.h"

namespace smol
{
namespace filesystem
{
class path::iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = smol::filesystem::path::string_type;
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type *;
    using reference = const value_type &;

    iterator(const value_type &p_path, std::size_t p_pos) : m_path{&p_path}, m_pos{p_pos}
    {
        advance();
    }

    auto operator*() const -> reference { return m_part; }
    auto operator->() const -> pointer { return &m_part; }

    auto operator++() -> iterator & { advance(); return *this; }
    auto operator++(int) -> iterator { iterator tmp = *this; ++(*this); return tmp; }

    auto next() -> iterator { iterator tmp = *this; ++tmp; return tmp; }

    friend auto operator==(const iterator &p_lhs, const iterator &p_rhs) -> bool
    {
        return p_lhs.m_pos == p_rhs.m_pos && p_lhs.m_path == p_rhs.m_path;
    }

    friend auto operator!=(const iterator &p_lhs, const iterator &p_rhs) -> bool
    {
        return !(p_lhs == p_rhs);
    }

private:
    const value_type *m_path;
    std::size_t m_pos;
    value_type m_part;

    auto advance() -> void
    {
        if (m_pos == std::string::npos) return;

        if (m_pos == 0 && *m_path->cbegin() == preferred_separator) {
            m_part = value_type{m_path->cbegin(), m_path->cbegin() + 1};
            m_pos = 1;
            return;
        }

        smol::string<1> pattern{"/"};
        const auto *start_it = find_first_not_of(m_path->cbegin() + m_pos, m_path->cend(), pattern.begin(), pattern.end());
        if (start_it == m_path->cend()) {
            m_pos = std::string::npos;
            return;
        }

        const auto *end_it = std::find(start_it, m_path->cend(), preferred_separator);
        m_part = value_type{start_it, end_it};
        m_pos = static_cast<std::size_t>(std::distance(m_path->cbegin(), end_it));
    }
};

path::path(string_type &&p_str) : path{p_str} {}

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

auto path::operator+=(STD_OR_SMOL::string_view p_str) -> path &
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
    return *this += STD_OR_SMOL::string_view(&p_val, 1);
}

auto path::native() const noexcept -> const string_type & { return m_path; }

auto path::lexically_normal() const -> path
{
    if (empty()) {
        return {};
    }

    path norm_p;
    if (has_root_directory()) {
        norm_p += preferred_separator;
    }

    auto curr = begin();
    auto end_it = end();
    for (; curr != end_it; ++curr) {
        auto next_it = curr.next();
        if (next_it != end_it && *next_it == "..") {
            curr = next_it;
            continue;
        }
        
        auto part = *curr;
        if (!part.empty() && part != ".") {
            if (part != "/") {
                norm_p += part;
                if ((next_it != end_it) || (next_it == end_it && !has_filename())) {
                    norm_p += preferred_separator;
                }
            }
        }
    }

    if (norm_p.empty()) {
        norm_p += '.';
    }

    return norm_p;
}

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

auto path::begin() const -> iterator
{
    return iterator{m_path, 0};
}

auto path::end() const -> iterator
{
    return iterator{m_path, std::string::npos};
}
} // namespace filesystem
} // namespace smol
