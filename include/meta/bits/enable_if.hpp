#ifndef META_BITS_ENABLE_IF
#define META_BITS_ENABLE_IF

#include "meta/bits/identity.hpp"

namespace stl {

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> : identity<T> {};

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

} // namespace stl

#endif // META_BITS_ENABLE_IF
