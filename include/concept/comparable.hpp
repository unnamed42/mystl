#ifndef CONCEPT_COMPARABLE
#define CONCEPT_COMPARABLE

#include "meta/sfinae.hpp"
#include "meta/bits/declval.hpp"

namespace stl {

namespace detail {

    template <class A, class B>
    using eq_impl = decltype(stl::declval<A>() == stl::declval<B>());

    template <class A, class B>
    using ineq_impl = decltype(stl::declval<A>() != stl::declval<B>());

    template <class A, class B>
    using lt_impl = decltype(stl::declval<A>() < stl::declval<B>());

} // namespace detail

template <class A, class B>
struct equality_comparable
    : is_detected<detail::eq_impl, A, B> {};

template <class A, class B>
struct inequality_comparable
    : is_detected<detail::ineq_impl, A, B> {};

template <class A, class B>
struct less_than_comparable
    : is_detected<detail::lt_impl, A, B> {};

} // namespace stl

#endif // CONCEPT_COMPARABLE
