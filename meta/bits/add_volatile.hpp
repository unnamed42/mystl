#ifndef META_BITS_ADD_VOLATILE
#define META_BITS_ADD_VOLATILE

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct add_volatile : identity<volatile T> {};
template <class T> using  add_volatile_t = typename add_volatile<T>::type;

} // namespace stl

#endif // META_BITS_ADD_VOLATILE
