#ifndef META_IS_MEMBER_POINTER
#define META_IS_MEMBER_POINTER

#include "meta/base.hpp"
#include "meta/cv.hpp"
#include "meta/logic.hpp"
#include "meta/is_function.hpp"

namespace stl {

namespace detail {

    template <class T>
    struct is_member_pointer : false_type {};

    template <class T, class Class>
    struct is_member_pointer<T Class::*> : true_type {};

    template <class T>
    struct is_member_function_pointer : false_type {};

    template <class T, class Class>
    struct is_member_function_pointer<T Class::*> : is_function<T> {};

} // namespace detail

template <class T>
struct is_member_pointer :
    detail::is_member_pointer<remove_cv_t<T>> {};
template <class T>
constexpr inline bool is_member_pointer_v = is_member_pointer<T>::value;

template <class T>
struct is_member_function_pointer
    : detail::is_member_function_pointer<remove_cv_t<T>> {};
template <class T>
constexpr inline bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

template <class T>
struct is_member_object_pointer
    : and_<is_member_pointer<T>, not_<is_member_function_pointer<T>> > {};
template <class T>
constexpr inline bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

} // namespace stl

#endif // META_IS_MEMBER_POINTER
