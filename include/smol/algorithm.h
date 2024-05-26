#pragma once

namespace smol
{
template <class InputIt, class ForwardIt>
auto find_first_not_of(InputIt p_first, InputIt p_last,
                       ForwardIt p_s_first, ForwardIt p_s_last) -> InputIt
{
    for (; p_first != p_last; ++p_first) {
        for (auto it = p_s_first; it != p_s_last; ++it) {
            if (*p_first != *it) {
                return p_first;
            }
        }
    }
    return p_last;
}
} // namespace smol
