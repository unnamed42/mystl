#ifndef META_IS_MEMBER_POINTER
#define META_IS_MEMBER_POINTER

#include "meta/op/logic.hpp"
#include "meta/base/constant.hpp"
#include "meta/check/is_function.hpp"
#include "meta/cvref/remove_cvref.hpp"

namespace stl::meta {

namespace detail {

    template <class T>
    struct is_member_pointer_impl : false_type {};

    template <class T, class Class>
    struct is_member_pointer_impl<T Class::*> : true_type {};

    template <class T>
    struct is_member_function_pointer_impl : false_type {};

    template <class T, class Class>
    struct is_member_function_pointer_impl<T Class::*> : is_function<T> {};

} // namespace detail

template <class T>
struct is_member_pointer :
    detail::is_member_pointer_impl<remove_cv_t<T>> {};

template <class T>
struct is_member_function_pointer
    : detail::is_member_function_pointer_impl<remove_cv_t<T>> {};

template <class T>
struct is_member_object_pointer
    : and_< is_member_pointer<T>, not_<is_member_function_pointer<T>> > {};

} // namespace stl::meta

#endif // META_IS_MEMBER_POINTER
