#ifndef META_IS_CVREF
#define META_IS_CVREF

#include "def.hpp"

#include "meta/base/constant.hpp"

namespace stl::meta {

template <class T> struct is_const          : false_type {};
template <class T> struct is_const<const T> : true_type  {};

template <class T> struct is_volatile             : false_type {};
template <class T> struct is_volatile<volatile T> : true_type  {};

template <class T> struct is_pointer     : false_type {};
template <class T> struct is_pointer<T*> : true_type  {};

template <class T> struct is_array                 : false_type {};
template <class T, size_t N> struct is_array<T[N]> : true_type  {};

template <class T> struct is_reference      : false_type {};
template <class T> struct is_reference<T&>  : true_type  {};
template <class T> struct is_reference<T&&> : true_type  {};

template <class T> struct is_lvalue_reference     : false_type {};
template <class T> struct is_lvalue_reference<T&> : true_type  {};

template <class T> struct is_rvalue_reference      : false_type {};
template <class T> struct is_rvalue_reference<T&&> : true_type  {};

} // namespace stl::meta

#endif // META_IS_CVREF
