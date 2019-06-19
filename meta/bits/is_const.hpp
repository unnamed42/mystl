#ifndef META_BITS_IS_CONST
#define META_BITS_IS_CONST

#include "meta/bits/constant.hpp"

namespace stl {

template <class T> struct is_const          : false_type {};
template <class T> struct is_const<const T> : true_type  {};
template <class T> constexpr inline bool is_const_v = is_const<T>::value;

} // namespace stl

#endif // META_BITS_IS_CONST
