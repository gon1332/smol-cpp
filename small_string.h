#pragma once

#include <cstdint>
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

    small_string() { nulify(); }

    template <class Source>
    explicit small_string(const Source &source) { copy(source); }

    [[nodiscard]] auto begin() const -> iterator { return m_string.begin(); }
    [[nodiscard]] auto end() const -> iterator { return m_string.begin() + m_length; }

    [[nodiscard]] auto empty() const noexcept -> bool { return m_length == 0U; }
    [[nodiscard]] auto length() const noexcept -> size_type { return m_length; }

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
} // namespace gon
