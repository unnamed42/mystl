#ifndef META_BITS_IS_SAME
#define META_BITS_IS_SAME

#include "meta/bits/constant.hpp"

namespace stl {

template <class T, class U> struct is_same       : false_type {};
template <class T>          struct is_same<T, T> : true_type  {};
template <class T, class U> constexpr inline bool is_same_v = is_same<T, U>::value;

} // namespace stl

#endif // META_BITS_IS_SAME
