#ifndef META_ADD_CVREF
#define META_ADD_CVREF

#include "meta/base/type.hpp"

namespace stl::meta {

namespace detail {

    template <class T>
    auto add_lvalue_ref(int) -> type<T&>;
    template <class T>
    auto add_lvalue_ref(...) -> type<T>;

    template <class T>
    auto add_rvalue_ref(int) -> type<T&&>;
    template <class T>
    auto add_rvalue_ref(...) -> type<T>;

} // namespace detail

template <class T> struct add_const : type<T> {};
template <class T> using  add_const_t = typename add_const<T>::type;

template <class T> struct add_volatile : type<volatile T> {};
template <class T> using  add_volatile_t = typename add_volatile<T>::type;

template <class T> struct add_cv : add_const<add_volatile_t<T>> {};
template <class T> using  add_cv_t = typename add_cv<T>::type;

template <class T> struct add_pointer : type<T*> {};
template <class T> using  add_pointer_t = typename add_pointer<T>::type;

template <class T> struct add_lvalue_reference : decltype(detail::add_lvalue_ref<T>(0)) {};
template <class T> using  add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template <class T> struct add_rvalue_reference : decltype(detail::add_rvalue_ref<T>(0)) {};
template <class T> using  add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

} // namespace stl::meta

#endif // META_ADD_CVREF
