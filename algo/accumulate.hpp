#ifndef ALGORITHM_ACCUMULATE
#define ALGORITHM_ACCUMULATE

#include "algo/detail/sentinel.hpp"
#include "meta/sfinae/enable_if.hpp"
#include "utility/bits/forward.hpp"
#include "container/acccess.hpp"

namespace stl {

template <class InputIt, class SentinelIt, class T>
constexpr auto accumulate(InputIt first, SentinelIt last, T init)
    -> meta::enable_if_t<detail::is_sentinel<SentinelIt, InputIt>{}, T> {
    for(; first != last; ++first)
        init = move(init) + *first;
    return init;
}

template <class InputIt, class SentinelIt, class T, class Callable>
constexpr auto accumulate(InputIt first, SentinelIt last, T init, Callable &&call)
    -> meta::enable_if_t<detail::is_sentinel<SentinelIt, InputIt>{}, T> {
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
