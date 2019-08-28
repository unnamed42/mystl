#ifndef META_ENABLE_IF
#define META_ENABLE_IF

#include "meta/base/type.hpp"

namespace stl::meta {

template <bool B, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> : type<T> {};

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

} // namespace stl::meta

#endif // META_ENABLE_IF
