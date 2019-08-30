#ifndef ALGORITHM_ACCUMULATE
#define ALGORITHM_ACCUMULATE

#include "utility/bits/forward.hpp"

#include "container/bits/access.hpp"

namespace stl {

template <class InputIt, class SentinelIt, class T>
constexpr T accumulate(InputIt first, SentinelIt last, T init) {
    for(; first != last; ++first)
        init = move(init) + *first;
    return init;
}

template <class InputIt, class SentinelIt, class T, class Callable>
constexpr T accumulate(InputIt first, SentinelIt last, T init, Callable &&call) {
    for(; first != last; ++first)
        init = call(move(init), *first);
    return init;
}

template <class Container, class T>
constexpr T accumulate(Container &&cont, T init) {
    return accumulate(begin(cont), end(cont), move(init));
}

template <class Container, class T, class Callable>
constexpr T accumulate(Container &&cont, T init, Callable &&call) {
    return accumulate(begin(cont), end(cont), move(init), forward<Callable>(call));
}

} // namespace  stl

#endif // ALGORITHM_ACCUMULATE
