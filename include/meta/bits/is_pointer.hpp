#ifndef META_BITS_IS_POINTER
#define META_BITS_IS_POINTER

#include "meta/bits/constant.hpp"

namespace stl {

template <class T> struct is_pointer     : false_type {};
template <class T> struct is_pointer<T*> : true_type  {};
template <class T> constexpr inline bool is_pointer_v = is_pointer<T>::value;

} // namespace stl

#endif // META_BITS_IS_POINTER
