#ifndef META_BITS_REMOVE_POINTER
#define META_BITS_REMOVE_POINTER

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct remove_pointer                    : identity<T> {};
template <class T> struct remove_pointer<T*>                : identity<T> {};
template <class T> struct remove_pointer<T* const>          : identity<T> {};
template <class T> struct remove_pointer<T* volatile>       : identity<T> {};
template <class T> struct remove_pointer<T* const volatile> : identity<T> {};
template <class T> using  remove_pointer_t = typename remove_pointer<T>::type;

} // namespace stl

#endif // META_BITS_REMOVE_POINTER
