#ifndef META_BITS_ADD_CONST
#define META_BITS_ADD_CONST

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct add_const : identity<const T> {};
template <class T> using  add_const_t = typename add_const<T>::type;

} // namespace stl

#endif // META_BITS_ADD_CONST
