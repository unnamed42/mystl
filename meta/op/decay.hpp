#ifndef META_DECAY
#define META_DECAY

#include "meta/op/condition.hpp"
#include "meta/cvref/add_cvref.hpp"
#include "meta/cvref/remove_cvref.hpp"
#include "meta/check/is_cvref.hpp"
#include "meta/check/is_function.hpp"

namespace stl::meta {

namespace detail {

    template <class T, bool> struct decay_impl;

    template <class T>
    struct decay_impl<T, true> : add_pointer<remove_extent_t<T>> {};

    template <class T>
    struct decay_impl<T, false> : condition_t<is_function<T>, add_pointer<T>, remove_cv<T>> {};

} // namespace detail

template<class T>
struct decay : detail::decay_impl<remove_reference_t<T>, is_array<remove_reference_t<T>>{}> {};

template <class T> using decay_t = typename decay<T>::type;

} // namespace stl::meta

#endif // META_DECAY
