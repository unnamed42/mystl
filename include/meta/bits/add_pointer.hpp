#ifndef META_BITS_ADD_POINTER
#define META_BITS_ADD_POINTER

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct add_pointer : identity<T*> {};
template <class T> using  add_pointer_t = typename add_pointer<T>::type;

} // namespace stl

#endif // META_BITS_ADD_POINTER
