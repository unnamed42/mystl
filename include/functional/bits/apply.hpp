#ifndef FUNCTIONAL_BITS_APPLY
#define FUNCTIONAL_BITS_APPLY

#include "def.hpp"

#include "utility/bits/forward.hpp"
#include "utility/bits/get_fwd.hpp"
#include "utility/bits/tuple_index.hpp"

#include "functional/bits/invoke.hpp"

namespace stl {

namespace detail {

    template <class F, class Tuple, size_t ...Idx>
    constexpr decltype(auto) apply_impl(F &&f, Tuple &&tuple, index_sequence<Idx...>) {
        return invoke(forward<F>(f), get<Idx>(forward<Tuple>(tuple))...);
    }

    template <class F, class Tuple1, size_t ...Idx1, class Tuple2, size_t ...Idx2>
    constexpr decltype(auto) apply2_impl(F &&f, Tuple1 &&t1, index_sequence<Idx1...>,
                                                Tuple2 &&t2, index_sequence<Idx2...>) {
        return invoke(forward<F>(f), get<Idx1>(forward<Tuple1>(t1))...,
                                     get<Idx2>(forward<Tuple2>(t2))...);
    }

} // namespace detail

template <class F, class Tuple>
constexpr decltype(auto) apply(F &&f, Tuple &&tuple) {
    return detail::apply_impl(forward<F>(f), forward<Tuple>(tuple),
                              tuple_index_t<Tuple>{});
}

template <class F, class Tuple1, class Tuple2>
constexpr decltype(auto) apply2(F &&f, Tuple1 &&t1, Tuple2 &&t2) {
    return detail::apply2_impl(forward<F>(f),
                               forward<Tuple1>(t1), tuple_index_t<Tuple1>{},
                               forward<Tuple2>(t2), tuple_index_t<Tuple2>{});
}

} // namespace stl

#endif // FUNCTIONAL_BITS_APPLY
