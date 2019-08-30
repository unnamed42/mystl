#ifndef META_BITS_IS_VOLATILE
#define META_BITS_IS_VOLATILE

#include "meta/bits/constant.hpp"

namespace stl {

template <class T> struct is_volatile             : false_type {};
template <class T> struct is_volatile<volatile T> : true_type  {};
template <class T> constexpr inline bool is_volatile_v = is_volatile<T>::value;

} // namespace stl

#endif // META_BITS_IS_VOLATILE
