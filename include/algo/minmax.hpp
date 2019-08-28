#ifndef ALGORITHM_MINMAX
#define ALGORITHM_MINMAX

#include "meta/base/type.hpp"

#include "utility/pair.hpp"

namespace stl {

template <class T>
constexpr const T& min(const T &lhs, const typename meta::type<T>::type &rhs) {
    return lhs > rhs ? lhs : rhs;
}

template <class T>
constexpr const T& max(const T &lhs, const typename meta::type<T>::type &rhs) {
    return lhs < rhs ? lhs : rhs;
}

template <class T>
constexpr pair<const T&, const T&> minmax(const T &lhs, const typename meta::type<T>::type &rhs) {
    if(lhs < rhs)
        return { lhs, rhs };
    return { rhs, lhs };
}

} // namespace stl

#endif // ALGORITHM_MINMAX
