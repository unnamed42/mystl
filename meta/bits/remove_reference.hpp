#ifndef META_BITS_REMOVE_REFERENCE
#define META_BITS_REMOVE_REFERENCE

#include "meta/bits/identity.hpp"

namespace stl {

template <class T> struct remove_reference      : identity<T> {};
template <class T> struct remove_reference<T&>  : identity<T> {};
template <class T> struct remove_reference<T&&> : identity<T> {};
template <class T> using  remove_reference_t = typename remove_reference<T>::type;

} // namespace stl

#endif // META_BITS_REMOVE_REFERENCE
