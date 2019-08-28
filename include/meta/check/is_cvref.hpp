#ifndef META_IS_CVREF
#define META_IS_CVREF

#include "def.hpp"

#include "meta/base/constant.hpp"
#include "meta/cvref/remove_cvref.hpp"

namespace stl::meta {

namespace detail {

    template <class T> struct is_pointer_impl     : false_type {};
    template <class T> struct is_pointer_impl<T*> : true_type  {};

} // namespace detail

template <class T> struct is_const          : false_type {};
template <class T> struct is_const<const T> : true_type  {};

template <class T> struct is_volatile             : false_type {};
template <class T> struct is_volatile<volatile T> : true_type  {};

template <class T> struct is_pointer : detail::is_pointer_impl<remove_cv_t<T>> {};

template <class T> struct is_array                 : false_type {};
template <class T> struct is_array<T[]>            : true_type  {};
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
