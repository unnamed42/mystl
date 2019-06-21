#ifndef ALGORITHM_FILL
#define ALGORITHM_FILL

#include "container/bits/access.hpp"

namespace stl {

template <class ForwardIt, class SentinelIt, class T>
constexpr void fill(ForwardIt first, SentinelIt last, const T &value) {
    for(; first != last; ++first)
        *first = value;
}

template <class Container, class T>
constexpr inline void fill(Container &cont, const T &value) {
    fill(begin(cont), end(cont), value);
}

} // namespace stl

#endif // ALGORITHM_FILL
