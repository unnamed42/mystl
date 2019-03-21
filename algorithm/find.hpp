#ifndef ALGORITHM_FIND
#define ALGORITHM_FIND

#include "utility/forward.hpp"
#include "container/access.hpp"

namespace stl {

template <class InputIt, class SentinelIt, class T>
InputIt find(InputIt first, SentinelIt last, const T &val) {
    while(first != last) {
        if(*first == val)
            break;
        ++first;
    }
    return first;
}

template <class Container, class T>
auto find(Container &&cont, const T &val) {
    return find(begin(cont), end(cont), val);
}

template <class InputIt, class SentinelIt, class T, class Predicate>
InputIt find_if(InputIt first, SentinelIt last, Predicate &&pred) {
    while(first != last) {
        if(pred(*first))
            break;
        ++first;
    }
    return first;
}

template <class Container, class Predicate>
auto find_if(Container &&cont, Predicate &&pred) {
    return find_if(begin(cont), end(cont), forward<Predicate>(pred));
}

template <class InputIt, class SentinelIt, class T>
InputIt find_not(InputIt first, SentinelIt last, const T &val) {
    return find_if(first, last, [&val](auto &&v) {
        return v != val;
    });
}

template <class Container, class T>
InputIt find_not(Container &&cont, const T &val) {
    return find_not(begin(cont), end(cont), val);
}

} // namespace stl

#endif // ALGORITHM_FIND
