#pragma once

#include <algorithm>

namespace smol
{
template <class InputIt, class ForwardIt>
auto find_first_not_of(InputIt p_first, InputIt p_last,
                       ForwardIt p_s_first, ForwardIt p_s_last) -> InputIt
{
    for (; p_first != p_last; ++p_first) {
        auto pred = [p_first](char p_symbol) { return *p_first == p_symbol; };
        if (std::none_of(p_s_first, p_s_last, pred))
            return p_first;
    }
    return p_last;
}
} // namespace smol
