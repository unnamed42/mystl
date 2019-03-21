#ifndef ALGORITHM_MINMAX_ELEMENT
#define ALGORITHM_MINMAX_ELEMENT

#include "meta/sfinae.hpp"
#include "utility/pair.hpp"
#include "utility/forward.hpp"
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
    return detail::select_element(first, last, stl::forward<Comparator>(cmp));
}

template <class InputIt, class SentinelIt, class = stl::satisfied<stl::sentinel<SentinelIt, InputIt>> >
InputIt min_element(InputIt first, SentinelIt last) {
    return detail::select_element(first, last, stl::less<>{});
}

template <class Container, class Comparator, class = stl::satisfied<stl::callable<Comparator>> >
auto min_element(Container &&cont, Comparator &&cmp) {
    return detail::select_element(stl::begin(cont), stl::end(cont), stl::forward<Comparator>(cmp));
}

template <class Container>
auto min_element(Container &&cont) {
    return detail::select_element(stl::begin(cont), stl::end(cont), stl::less<>{});
}

template <class InputIt, class SentinelIt, class Comparator>
InputIt max_element(InputIt first, SentinelIt last, Comparator &&cmp) {
    return detail::select_element(first, last, stl::forward<Comparator>(cmp));
}

template <class InputIt, class SentinelIt, class = stl::satisfied<stl::sentinel<SentinelIt, InputIt>> >
auto max_element(InputIt first, SentinelIt last) {
    return detail::select_element(first, last, stl::greater<>{});
}

template <class Container, class Comparator, class = stl::satisfied<stl::callable<Comparator>> >
auto max_element(Container &&cont, Comparator &&cmp) {
    return detail::select_element(stl::begin(cont), stl::end(cont), stl::forward<Comparator>(cmp));
}

template <class Container>
auto max_element(Container &&cont) {
    return detail::select_element(stl::begin(cont), stl::end(cont), stl::greater<>{});
}

template <class InputIt, class SentinelIt, class Less>
stl::pair<InputIt, InputIt> minmax_element(InputIt first, SentinelIt last, Less &&cmp) {
    InputIt min = first, max = first;
    for(; first != last; ++first) {
        if(cmp(*first, *min))
            min = first;
        if(!cmp(*first, *max))
            max = first;
    }
    return { min, max };
}

template <class InputIt, class SentinelIt, class = stl::satisfied<stl::sentinel<SentinelIt, InputIt>> >
auto minmax_element(InputIt first, SentinelIt last) {
    return stl::minmax_element(first, last, stl::less<>{});
}

template <class Container, class Less, class = stl::satisfied<stl::callable<Less>> >
auto minmax_element(Container &&cont, Less &&cmp) {
    return stl::minmax_element(stl::begin(cont), stl::end(cont), stl::forward<Less>(cmp));
}

template <class Container>
auto minmax_element(Container &&cont) {
    return stl::minmax_element(stl::begin(cont), stl::end(cont), stl::less<>{});
}

} // namespace stl

#endif // ALGORITHM_MINMAX_ELEMENT
