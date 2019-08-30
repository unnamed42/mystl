#ifndef UTILITY_BITS_SWAP
#define UTILITY_BITS_SWAP

#include "utility/bits/forward.hpp"

namespace stl {

template <class T>
constexpr void swap(T &t1, T &t2) {
    T tmp(move(t1));
    t1 = move(t2);
    t2 = move(tmp);
}

} // namespace stl

#endif // UTILITY_BITS_SWAP
