#ifndef META_BITS_ADD_REFERENCE
#define META_BITS_ADD_REFERENCE

#include "meta/bits/identity.hpp"

namespace stl {

namespace detail {

    template <class T>
    auto add_lvalue_ref(int) -> identity<T&>;
    template <class T>
    auto add_lvalue_ref(...) -> identity<T>;

    template <class T>
    auto add_rvalue_ref(int) -> identity<T&&>;
    template <class T>
    auto add_rvalue_ref(...) -> identity<T>;

} // namespace detail

template <class T> struct add_lvalue_reference : decltype(detail::add_lvalue_ref<T>(0)) {};
template <class T> using  add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

template <class T> struct add_rvalue_reference : decltype(detail::add_rvalue_ref<T>(0)) {};
template <class T> using  add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

} // namespace stl

#endif // META_BITS_ADD_REFERENCE
