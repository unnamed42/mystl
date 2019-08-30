#ifndef META_BITS_IS_REFERENCE_WRAPPER
#define META_BITS_IS_REFERENCE_WRAPPER

#include "meta/bits/constant.hpp"

namespace stl {

template <class T> class reference_wrapper;

template <class T> struct is_reference_wrapper                       : false_type {};
template <class T> struct is_reference_wrapper<reference_wrapper<T>> : true_type {};
template <class T> constexpr inline bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

} // namespace stl

#endif // META_BITS_IS_REFERENCE_WRAPPER
