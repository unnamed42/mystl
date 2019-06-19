#ifndef UTILITY_BITS_AS_CONST
#define UTILITY_BITS_AS_CONST

#include "meta/bits/add_const.hpp"

namespace stl {

template <class T>
constexpr add_const_t<T> as_const(T &t) noexcept { return t; }

template <class T>
void as_const(const T &&) = delete;

} // namespace stl

#endif // UTILITY_BITS_AS_CONST
