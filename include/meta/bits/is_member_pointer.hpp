#ifndef META_BITS_IS_MEMBER_POINTER
#define META_BITS_IS_MEMBER_POINTER

#include "meta/cvref.hpp"
#include "meta/bits/constant.hpp"
#include "meta/bits/logic.hpp"
#include "meta/bits/is_function.hpp"

namespace stl {

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
constexpr inline bool is_member_pointer_v = is_member_pointer<T>::value;

template <class T>
struct is_member_function_pointer
    : detail::is_member_function_pointer_impl<remove_cv_t<T>> {};
template <class T>
constexpr inline bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

template <class T>
struct is_member_object_pointer
    : and_<is_member_pointer<T>, not_<is_member_function_pointer<T>> > {};
template <class T>
constexpr inline bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

} // namespace stl

#endif // META_BITS_IS_MEMBER_POINTER
