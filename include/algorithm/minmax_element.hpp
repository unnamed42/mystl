#ifndef ALGORITHM_MINMAX_ELEMENT
#define ALGORITHM_MINMAX_ELEMENT

#include "meta/bits/enable_if.hpp"

#include "utility/pair.hpp"
#include "utility/bits/forward.hpp"

#include "concept/sentinel.hpp"
#include "concept/callable.hpp"

#include "container/bits/access.hpp"

#include "functional/relation.hpp"

namespace stl {

namespace detail {

    template <class InputIt, class SentinelIt, class Comparator>
    constexpr InputIt select_element(InputIt first, SentinelIt last, Comparator &&cmp) {
        auto selected = first;
        for(; first != last; ++first) {
            if(cmp(*first, *selected))
                selected = first;
        }
        return selected;
    }

} // namespace detail

template <class InputIt, class SentinelIt, class Comparator>
constexpr InputIt min_element(InputIt first, SentinelIt last, Comparator &&cmp) {
    return detail::select_element(first, last, forward<Comparator>(cmp));
}

template <class InputIt, class SentinelIt>
constexpr auto min_element(InputIt first, SentinelIt last)
    -> enable_if_t<sentinel<SentinelIt, InputIt>{}, InputIt> {
    return detail::select_element(first, last, lt<>{});
}

template <class Container, class Comparator, class = enable_if_t<callable<Comparator>{}> >
constexpr auto min_element(Container &&cont, Comparator &&cmp) {
    return detail::select_element(begin(cont), end(cont), forward<Comparator>(cmp));
}

template <class Container>
constexpr auto min_element(Container &&cont) {
    return detail::select_element(begin(cont), end(cont), lt<>{});
}

template <class InputIt, class SentinelIt, class Comparator>
constexpr InputIt max_element(InputIt first, SentinelIt last, Comparator &&cmp) {
    return detail::select_element(first, last, forward<Comparator>(cmp));
}

template <class InputIt, class SentinelIt>
constexpr auto max_element(InputIt first, SentinelIt last)
    -> enable_if_t<sentinel<SentinelIt, InputIt>{}, InputIt> {
    return detail::select_element(first, last, gt<>{});
}

template <class Container, class Comparator, class = enable_if_t<callable<Comparator>{}>>
constexpr auto max_element(Container &&cont, Comparator &&cmp) {
    return detail::select_element(begin(cont), end(cont), forward<Comparator>(cmp));
}

template <class Container>
constexpr auto max_element(Container &&cont) {
    return detail::select_element(begin(cont), end(cont), gt<>{});
}

template <class InputIt, class SentinelIt, class Less>
constexpr pair<InputIt, InputIt> minmax_element(InputIt first, SentinelIt last, Less &&cmp) {
    InputIt min = first, max = first;
    for(; first != last; ++first) {
        if(cmp(*first, *min))
            min = first;
        if(!cmp(*first, *max))
            max = first;
    }
    return { min, max };
}

template <class InputIt, class SentinelIt>
constexpr auto minmax_element(InputIt first, SentinelIt last)
    -> enable_if_t<sentinel<SentinelIt, InputIt>{}, InputIt> {
    return minmax_element(first, last, lt<>{});
}

template <class Container, class Less, class = enable_if_t<callable<Less>{}> >
constexpr auto minmax_element(Container &&cont, Less &&cmp) {
    return minmax_element(begin(cont), end(cont), forward<Less>(cmp));
}

template <class Container>
constexpr auto minmax_element(Container &&cont) {
    return minmax_element(begin(cont), end(cont), lt<>{});
}

} // namespace stl

#endif // ALGORITHM_MINMAX_ELEMENT
