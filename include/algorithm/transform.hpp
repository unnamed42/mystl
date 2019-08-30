#ifndef ALGORITHM_TRANSFORM
#define ALGORITHM_TRANSFORM

#include "utility/bits/forward.hpp"

#include "container/bits/access.hpp"

namespace stl {

template <class InputIt, class SentinelIt, class OutputIt, class Transformer>
constexpr OutputIt transform(InputIt first, SentinelIt last, OutputIt out, Transformer &&tran) {
    while(first != last) {
        *out++ = tran(*first++);
    }
    return out;
}

template <class Container, class OutputIt, class Transformer>
constexpr OutputIt transform(Container &&cont, OutputIt out, Transformer &&trans) {
    return transform(begin(cont), end(cont), out, forward<Transformer>(trans));
}

} // namespace stl

#endif // ALGORITHM_TRANSFORM
