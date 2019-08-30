#ifndef META_BITS_IS_ARRAY
#define META_BITS_IS_ARRAY

#include "def.hpp"

#include "meta/bits/constant.hpp"

namespace stl {

template <class T> struct is_array                 : false_type {};
template <class T, size_t N> struct is_array<T[N]> : true_type  {};
template <class T> constexpr inline bool is_array_v = is_array<T>::value;

} // namespace stl

#endif // META_BITS_IS_ARRAY
