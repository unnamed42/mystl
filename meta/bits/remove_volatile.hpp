#ifndef META_BITS_REMOVE_VOLATILE
#define META_BITS_REMOVE_VOLATILE

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct remove_volatile             : identity<T> {};
template <class T> struct remove_volatile<volatile T> : identity<T> {};
template <class T> using  remove_volatile_t = typename remove_volatile<T>::type;

} // namespace stl

#endif // META_BITS_REMOVE_VOLATILE
