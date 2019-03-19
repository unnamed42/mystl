#ifndef UTILITY_SWAP
#define UTILITY_SWAP

#include "utility/forward.hpp"

namespace rubbish {

template <class T>
void swap(T &t1, T &t2) {
    T tmp(move(t1));
    t1 = move(t2);
    t2 = move(tmp);
}

} // namespace rubbish

#endif // UTILITY_SWAP
