#ifndef ALGORITHM_FOR_EACH
#define ALGORITHM_FOR_EACH

#include "utility/bits/forward.hpp"

#include "container/bits/access.hpp"

namespace stl {

template <class InputIt, class SentinelIt, class Unary>
constexpr void for_each(InputIt first, SentinelIt last, Unary &&unary) {
    while(first != last) {
        if(!unary(*first))
            break;
        ++first;
    }
}

template <class Container, class Unary>
constexpr void for_each(Container &&cont, Unary &&unary) {
    for_each(begin(cont), end(cont), forward<Unary>(unary));
}

} // namespace stl

#endif // ALGORITHM_FOR_EACH
