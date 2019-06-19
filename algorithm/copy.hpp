#ifndef ALGORITHM_COPY
#define ALGORITHM_COPY

#include "utility/bits/forward.hpp"

#include "container/access.hpp"

namespace stl {

template <class InputIt, class SentinelIt, class OutputIt>
OutputIt copy(InputIt first, SentinelIt last, OutputIt out) {
    for(; first != last; ++out, ++first)
        *out = *first;
    return out;
}

template <class Container, class OutputIt>
OutputIt copy(Container &&cont, OutputIt out) {
    return copy(begin(cont), end(cont), out);
}

template <class InputIt, class SentinelIt, class OutputIt, class Predicate>
OutputIt copy_if(InputIt first, SentinelIt last, OutputIt out, Predicate &&pred) {
    for(; first != last; ++first) {
        if(pred(*first)) {
            *out = *first;
            ++out;
        }
    }
}

template <class Container, class OutputIt, class Predicate>
OutputIt copy_if(Container &&cont, OutputIt out, Predicate &&pred) {
    return copy_if(begin(cont), end(cont), out, forward<Predicate>(pred));
}

} // stl

#endif // ALGORITHM_COPY
