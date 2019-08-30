#ifndef UTILITY_DETAIL_TUPLE_TRAITS
#define UTILITY_DETAIL_TUPLE_TRAITS

#include "meta/bits/is_assignable.hpp"
#include "meta/bits/is_convertible.hpp"

#include "utility/bits/detail/tuples_foreach.hpp"

namespace stl { namespace detail {

template <class Dest, class Source>
struct tuple_assignable
    : tuples_foreach<is_assignable, Dest, Source> {};

template <class D, class S>
constexpr inline bool tuple_assignable_v = tuple_assignable<D, S>::value;

template <class From, class To>
struct tuple_convertible
    : tuples_foreach< is_convertible, From, To> {};

template <class F, class T>
constexpr inline bool tuple_convertible_v = tuple_convertible<F, T>::value;

}} // namespace stl::detail

#endif // UTILITY_DETAIL_TUPLE_TRAITS
