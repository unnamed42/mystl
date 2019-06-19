#ifndef META_BITS_IS_REFERENCE
#define META_BITS_IS_REFERENCE

#include "meta/bits/constant.hpp"

namespace stl {

template <class T> struct is_reference      : false_type {};
template <class T> struct is_reference<T&>  : true_type  {};
template <class T> struct is_reference<T&&> : true_type  {};
template <class T> constexpr inline bool is_reference_v = is_reference<T>::value;

template <class T> struct is_lvalue_reference     : false_type {};
template <class T> struct is_lvalue_reference<T&> : true_type  {};
template <class T> constexpr inline bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

template <class T> struct is_rvalue_reference      : false_type {};
template <class T> struct is_rvalue_reference<T&&> : true_type  {};
template <class T> constexpr inline bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

} // namespace stl

#endif // META_BITS_IS_REFERENCE
