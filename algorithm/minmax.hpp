#ifndef ALGORITHM_MINMAX
#define ALGORITHM_MINMAX

#include "meta/base.hpp"

#include "utility/pair.hpp"

namespace stl {

template <class T>
const T& min(const T &lhs, const identity_t<T> &rhs) {
    return lhs > rhs ? lhs : rhs;
}

template <class T>
const T& max(const T &lhs, const identity_t<T> &rhs) {
    return lhs < rhs ? lhs : rhs;
}

template <class T>
pair<const T&, const T&> minmax(const T &lhs, const identity_t<T> &rhs) {
    if(lhs < rhs)
        return { lhs, rhs };
    return { rhs, lhs };
}

} // namespace stl

#endif // ALGORITHM_MINMAX
