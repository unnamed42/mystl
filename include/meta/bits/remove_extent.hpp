#ifndef META_BITS_EXTENT
#define META_BITS_EXTENT

#include "def.hpp"

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct remove_extent                 : identity<T> {};
template <class T> struct remove_extent<T[]>            : identity<T> {};
template <class T, size_t N> struct remove_extent<T[N]> : identity<T> {};
template <class T> using  remove_extent_t = typename remove_extent<T>::type;

} // namespace stl

#endif // META_BITS_EXTENT
