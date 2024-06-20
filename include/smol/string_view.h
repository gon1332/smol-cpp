#pragma once

#include <cstdint>
#include <cstring>
#include <iterator>
#include <ostream>

namespace smol
{
class string_view
{
public:
    using value_type = char;
    using pointer = char *;
    using const_pointer = const char *;
    using reference = char &;
    using const_reference = const char &;
    using const_iterator = const_pointer;
    using iterator = const_iterator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    string_view() noexcept = default;
    string_view(const char *p_s, size_type p_count) : m_string{p_s}, m_length{p_count} {}
    string_view(const char *p_s) : m_string{p_s}, m_length{std::strlen(p_s)} {}
    string_view(std::nullptr_t) = delete;

    [[nodiscard]] auto begin() const noexcept -> const_iterator { return m_string; }
    [[nodiscard]] auto cbegin() const noexcept -> const_iterator { return m_string; }
    [[nodiscard]] auto end() const noexcept -> const_iterator { return begin() + m_length; }
    [[nodiscard]] auto cend() const noexcept -> const_iterator { return cbegin() + m_length; }

    auto operator[](size_type p_pos) const -> const_reference
    {
        return *(cbegin() + p_pos);
    }

    auto front() const -> const_reference { return operator[](0); }
    auto back() const -> const_reference { return operator[](size() - 1); }
    auto data() const -> const_pointer { return m_string; }

    [[nodiscard]] auto size() const noexcept -> size_type { return m_length; }
    [[nodiscard]] auto length() const noexcept -> size_type { return size(); }
    [[nodiscard]] auto empty() const noexcept -> bool { return size() == 0U; }

    friend auto operator==(string_view p_lhs, string_view p_rhs) noexcept -> bool
    {
        if (p_lhs.length() != p_rhs.length()) {
            return false;
        }
        const auto *it_l = p_lhs.cbegin();
        const auto *it_r = p_rhs.cbegin();
        const auto *end_l = p_lhs.cend();
        const auto *end_r = p_rhs.cend();
        for (; it_l != end_l && it_r != end_r; std::advance(it_l, 1), std::advance(it_r, 1)) {
            if (*it_l != *it_r) {
                return false;
            }
        }
        return true;
    }

    friend auto operator!=(string_view p_lhs, string_view p_rhs) noexcept -> bool
    {
        return !(p_lhs == p_rhs);
    }

    friend auto operator<<(std::ostream &p_os, string_view p_v) -> std::ostream &
    {
        for (const auto &item : p_v) {
            p_os << item;
        }
        return p_os;
    }

private:
    const_pointer m_string{nullptr};
    size_type m_length{0U};
};
} // namespace smol
