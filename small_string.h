#pragma once

#include <cstdint>
#include <array>
#include <string_view>

namespace gon
{
template <std::size_t Size>
class small_string
{
public:
    using value_type = char;
    using buffer_type = std::array<value_type, Size + 1>;
    using size_type = std::size_t;
    using iterator = typename buffer_type::iterator;
    using const_iterator = typename buffer_type::const_iterator;

    small_string() { nulify(); }

    template <class Source>
    explicit small_string(const Source &source) { copy(source); }

    [[nodiscard]] auto begin() -> iterator { return m_string.begin(); }
    [[nodiscard]] auto cbegin() const -> const_iterator { return m_string.cbegin(); }
    [[nodiscard]] auto end() -> iterator { return m_string.begin() + m_length; }
    [[nodiscard]] auto cend() const -> const_iterator { return m_string.cbegin() + m_length; }

    [[nodiscard]] auto empty() const noexcept -> bool { return m_length == 0U; }
    [[nodiscard]] auto size() const noexcept -> size_type { return m_length; }
    [[nodiscard]] auto length() const noexcept -> size_type { return size(); }

    auto operator[](size_type pos) -> value_type &
    {
        return *(begin() + pos);
    }

    auto operator[](size_type pos) const -> const value_type &
    {
        return *(cbegin() + pos);
    }

    auto front() -> value_type & { return operator[](0); }
    auto front() const -> const value_type & { return operator[](0); }
    auto back() -> value_type & { return operator[](size() - 1); }
    auto back() const -> const value_type & { return operator[](size() - 1); }

    auto c_str() const noexcept -> const value_type *
    {
        return m_string.data();
    }

    auto append(size_type count, value_type ch) -> small_string<Size> &
    {
        for (; count > 0 && m_length < Size; --count, ++m_length) {
            m_string.at(m_length) = ch;
        }
        nulify();
        return *this;
    }

    auto append(const value_type *s) -> small_string<Size> &
    {
        copy(s);
        return *this;
    }

    auto operator+=(value_type ch) -> small_string<Size> &
    {
        return append(1U, ch);
    }

    auto operator+=(const value_type *s) -> small_string<Size> &
    {
        return append(s);
    }

private:
    auto nulify() -> void { m_string.at(m_length) = '\0'; }

    auto copy(std::string_view sv) -> void
    {
        if (sv.size() > 0) {
            for (const auto c : sv) {
                if (m_length < Size) {
                    m_string.at(m_length) = c;
                } else {
                    break;
                }
                ++m_length;
            }
            nulify();
        }
    }

    buffer_type m_string;
    size_type m_length{0U};
};

template <std::size_t SizeL, std::size_t SizeR>
auto operator==(const small_string<SizeL> &lhs,
                const small_string<SizeR> &rhs) -> bool
{
    return lhs.c_str() == rhs;
}

template <std::size_t SizeL, std::size_t SizeR>
auto operator!=(const small_string<SizeL> &lhs,
                const small_string<SizeR> &rhs) -> bool
{
    return !(lhs == rhs);
}

template <std::size_t Size>
auto operator==(const small_string<Size> &lhs, const char *rhs) -> bool
{
    const char *l = lhs.c_str();
    const char *r = rhs;
    while (*l && *l == *r) {
        ++l;
        ++r;
    }
    return *l == *r;
}

template <std::size_t Size>
auto operator==(const char *lhs, const small_string<Size> rhs) -> bool
{
    return rhs == lhs;
}

template <std::size_t Size>
auto operator!=(const small_string<Size> &lhs, const char *rhs) -> bool
{
    return !(lhs == rhs);
}

template <std::size_t Size>
auto operator!=(const char *lhs, const small_string<Size> &rhs) -> bool
{
    return rhs != lhs;
}

template <std::size_t Size>
auto operator==(const small_string<Size> &lhs, const std::string_view &rhs) -> bool
{
    if (lhs.length() != rhs.length()) {
        return false;
    }
    auto it_l = lhs.cbegin();
    auto it_r = rhs.cbegin();
    auto end_l = lhs.cend();
    auto end_r = rhs.cend();
    for (; it_l != end_l && it_r != end_r; ++it_l, ++it_r) {
        if (*it_l != *it_r) {
            return false;
        }
    }
    return true;
}

template <std::size_t Size>
auto operator==(const std::string_view &lhs, const small_string<Size> rhs) -> bool
{
    return rhs == lhs;
}

template <std::size_t Size>
auto operator!=(const small_string<Size> &lhs, const std::string_view &rhs) -> bool
{
    return !(lhs == rhs);
}

template <std::size_t Size>
auto operator!=(const std::string_view &lhs, const small_string<Size> &rhs) -> bool
{
    return rhs != lhs;
}

template <class OStream, std::size_t Size>
auto operator<<(OStream &os, const small_string<Size> &str) -> OStream &
{
    os << std::string_view{str.c_str()};
    return os;
}
} // namespace gon
