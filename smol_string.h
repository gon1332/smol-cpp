#pragma once

#include <cstdint>
#include <array>
#include <iterator>
#include <string_view>

namespace smol
{
template <std::size_t Size>
class string
{
public:
    using value_type = char;
    using buffer_type = std::array<value_type, Size + 1>;
    using size_type = std::size_t;
    using iterator = typename buffer_type::iterator;
    using const_iterator = typename buffer_type::const_iterator;

    string() { nulify(0); }

    explicit string(const value_type *p_str) { copy(p_str); }

    template <class Source>
    explicit string(const Source &p_source) { copy(std::string_view{p_source}); }

    template <class InputIt>
    string(InputIt p_first, InputIt p_last) { copy(p_first, p_last); }

    template <std::size_t SizeOther>
    string(const string<SizeOther> &p_str) { *this = p_str; }

    template <std::size_t SizeOther>
    auto operator=(const string<SizeOther> &p_str) -> string &
    {
        if (this != p_str) {
            clear();
            copy(p_str);
        }
        return *this;
    }

    auto operator=(const value_type *p_str) -> string &
    {
        clear();
        copy(p_str);
        return *this;
    }

    [[nodiscard]] auto begin() -> iterator { return m_string.begin(); }
    [[nodiscard]] auto cbegin() const -> const_iterator { return m_string.cbegin(); }
    [[nodiscard]] auto end() -> iterator { return m_string.begin() + m_length; }
    [[nodiscard]] auto cend() const -> const_iterator { return m_string.cbegin() + m_length; }

    [[nodiscard]] auto empty() const noexcept -> bool { return m_length == 0U; }
    [[nodiscard]] auto size() const noexcept -> size_type { return m_length; }
    [[nodiscard]] auto length() const noexcept -> size_type { return size(); }

    auto operator[](size_type p_pos) -> value_type &
    {
        return *(begin() + p_pos);
    }

    auto operator[](size_type p_pos) const -> const value_type &
    {
        return *(cbegin() + p_pos);
    }

    auto front() -> value_type & { return operator[](0); }
    auto front() const -> const value_type & { return operator[](0); }
    auto back() -> value_type & { return operator[](size() - 1); }
    auto back() const -> const value_type & { return operator[](size() - 1); }

    auto c_str() const noexcept -> const value_type *
    {
        return m_string.data();
    }

    auto clear() -> void
    {
        m_length = 0;
        nulify(0);
    }

    template <std::size_t SizeOther>
    auto append(const string<SizeOther> &p_str) -> string<Size> &
    {
        return append(p_str.c_str());
    }

    auto append(size_type p_count, value_type p_val) -> string<Size> &
    {
        for (; p_count > 0 && m_length < Size; --p_count, ++m_length) {
            m_string.at(m_length) = p_val;
        }
        nulify(m_length);
        return *this;
    }

    auto append(const value_type *p_str) -> string<Size> &
    {
        copy(p_str);
        return *this;
    }

    template <std::size_t SizeOther>
    auto operator+=(const string<SizeOther> &p_str) -> string<Size> &
    {
        return append(p_str);
    }

    auto operator+=(value_type p_val) -> string<Size> &
    {
        return append(1U, p_val);
    }

    auto operator+=(const value_type *p_str) -> string<Size> &
    {
        return append(p_str);
    }

private:
    auto nulify(size_type p_pos) -> void { m_string.at(p_pos) = '\0'; }

    template <class InputIt>
    auto copy(InputIt p_first, InputIt p_last) -> void
    {
        for (const auto *val = p_first; val != p_last; std::advance(val, 1)) {
            if (m_length < Size) {
                m_string.at(m_length) = *val;
            } else {
                break;
            }
            ++m_length;
        }
        nulify(m_length);
    }

    auto copy(std::string_view p_sv) -> void
    {
        copy(p_sv.begin(), p_sv.end());
    }

    buffer_type m_string;
    size_type m_length{0U};
};

template <std::size_t SizeL, std::size_t SizeR>
auto operator==(const string<SizeL> &p_lhs,
                const string<SizeR> &p_rhs) -> bool
{
    return p_lhs.c_str() == p_rhs;
}

template <std::size_t SizeL, std::size_t SizeR>
auto operator!=(const string<SizeL> &p_lhs,
                const string<SizeR> &p_rhs) -> bool
{
    return !(p_lhs == p_rhs);
}

template <std::size_t Size>
auto operator==(const string<Size> &p_lhs, const char *p_rhs) -> bool
{
    return std::string_view{p_lhs.c_str()} == std::string_view{p_rhs};
}

template <std::size_t Size>
auto operator==(const char *p_lhs, const string<Size> p_rhs) -> bool
{
    return p_rhs == p_lhs;
}

template <std::size_t Size>
auto operator!=(const string<Size> &p_lhs, const char *p_rhs) -> bool
{
    return !(p_lhs == p_rhs);
}

template <std::size_t Size>
auto operator!=(const char *p_lhs, const string<Size> &p_rhs) -> bool
{
    return p_rhs != p_lhs;
}

template <std::size_t Size>
auto operator==(const string<Size> &p_lhs, const std::string_view &p_rhs) -> bool
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

template <std::size_t Size>
auto operator==(const std::string_view &p_lhs, const string<Size> p_rhs) -> bool
{
    return p_rhs == p_lhs;
}

template <std::size_t Size>
auto operator!=(const string<Size> &p_lhs, const std::string_view &p_rhs) -> bool
{
    return !(p_lhs == p_rhs);
}

template <std::size_t Size>
auto operator!=(const std::string_view &p_lhs, const string<Size> &p_rhs) -> bool
{
    return p_rhs != p_lhs;
}

template <class OStream, std::size_t Size>
auto operator<<(OStream &p_os, const string<Size> &p_str) -> OStream &
{
    p_os << std::string_view{p_str.c_str()};
    return p_os;
}
} // namespace smol
