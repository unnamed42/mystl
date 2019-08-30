#ifndef META_BITS_REMOVE_CONST
#define META_BITS_REMOVE_CONST

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct remove_const          : identity<T> {};
template <class T> struct remove_const<const T> : identity<T> {};
template <class T> using  remove_const_t = typename remove_const<T>::type;

} // namespace stl

#endif // META_BITS_REMOVE_CONST
