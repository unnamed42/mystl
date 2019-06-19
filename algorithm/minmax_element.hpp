#ifndef ALGORITHM_MINMAX_ELEMENT
#define ALGORITHM_MINMAX_ELEMENT

#include "meta/bits/enable_if.hpp"

#include "utility/pair.hpp"
#include "utility/bitsforward.hpp"

#include "concept/sentinel.hpp"
#include "concept/callable.hpp"

#include "container/access.hpp"

#include "functional/relation.hpp"

namespace stl {

namespace detail {

    template <class InputIt, class SentinelIt, class Comparator>
    InputIt select_element(InputIt first, SentinelIt last, Comparator &&cmp) {
        auto selected = first;
        for(; first != last; ++first) {
            if(cmp(*first, *selected))
                selected = first;
        }
        return selected;
    }

} // namespace detail

template <class InputIt, class SentinelIt, class Comparator>
InputIt min_element(InputIt first, SentinelIt last, Comparator &&cmp) {
    return detail::select_element(first, last, forward<Comparator>(cmp));
}

template <class InputIt, class SentinelIt, class = satisfied<sentinel<SentinelIt, InputIt>> >
InputIt min_element(InputIt first, SentinelIt last) {
    return detail::select_element(first, last, less<>{});
}

template <class Container, class Comparator, class = satisfied<callable<Comparator>> >
auto min_element(Container &&cont, Comparator &&cmp) {
    return detail::select_element(begin(cont), end(cont), forward<Comparator>(cmp));
}

template <class Container>
auto min_element(Container &&cont) {
    return detail::select_element(begin(cont), end(cont), less<>{});
}

template <class InputIt, class SentinelIt, class Comparator>
InputIt max_element(InputIt first, SentinelIt last, Comparator &&cmp) {
    return detail::select_element(first, last, forward<Comparator>(cmp));
}

template <class InputIt, class SentinelIt, class = satisfied<sentinel<SentinelIt, InputIt>> >
auto max_element(InputIt first, SentinelIt last) {
    return detail::select_element(first, last, greater<>{});
}

template <class Container, class Comparator, class = satisfied<callable<Comparator>> >
auto max_element(Container &&cont, Comparator &&cmp) {
    return detail::select_element(begin(cont), end(cont), forward<Comparator>(cmp));
}

template <class Container>
auto max_element(Container &&cont) {
    return detail::select_element(begin(cont), end(cont), greater<>{});
}

template <class InputIt, class SentinelIt, class Less>
pair<InputIt, InputIt> minmax_element(InputIt first, SentinelIt last, Less &&cmp) {
    InputIt min = first, max = first;
    for(; first != last; ++first) {
        if(cmp(*first, *min))
            min = first;
        if(!cmp(*first, *max))
            max = first;
    }
    return { min, max };
}

template <class InputIt, class SentinelIt, class = satisfied<sentinel<SentinelIt, InputIt>> >
auto minmax_element(InputIt first, SentinelIt last) {
    return minmax_element(first, last, less<>{});
}

template <class Container, class Less, class = satisfied<callable<Less>> >
auto minmax_element(Container &&cont, Less &&cmp) {
    return minmax_element(begin(cont), end(cont), forward<Less>(cmp));
}

template <class Container>
auto minmax_element(Container &&cont) {
    return minmax_element(begin(cont), end(cont), less<>{});
}

} // namespace stl

#endif // ALGORITHM_MINMAX_ELEMENT
