#ifndef UTILITY_DETAIL_TUPLE
#define UTILITY_DETAIL_TUPLE

#include "def.hpp"

#include "meta/bits/enable_if.hpp"
#include "meta/bits/index_sequence.hpp"

#include "utility/bits/forward.hpp"
#include "utility/bits/get_fwd.hpp"
#include "utility/bits/tuple_like.hpp"
#include "utility/bits/tuple_types.hpp"
#include "utility/bits/tuple_element.hpp"
#include "utility/bits/detail/tuple_leaf.hpp"

namespace stl { namespace detail {

template <class Idx, class ...Ts> struct tuple_impl;

template <size_t ...Idx, class ...Ts>
struct tuple_impl<index_sequence<Idx...>, Ts...> : tuple_leaf<Idx, Ts>... {

    constexpr tuple_impl() : tuple_leaf<Idx, Ts>()... {}

    template <size_t ...Idx1, class ...Ts1,
              size_t ...Idx2, class ...Ts2, class ...Values>
    explicit constexpr tuple_impl(index_sequence<Idx1...>, tuple_types<Ts1...>,
                        index_sequence<Idx2...>, tuple_types<Ts2...>, Values&& ...values)
        : tuple_leaf<Idx1, Ts1>(stl::forward<Values>(values))...,
          tuple_leaf<Idx2, Ts2>()... {}

    template < class Tuple, class = enable_if_t<tuple_like_v<Tuple>> >
    constexpr tuple_impl(Tuple &&t) : tuple_leaf<Idx, Ts> (
        stl::forward< tuple_element_t<Idx, make_tuple_types_t<Tuple>> >(get<Idx>(t))
    )... {}

    template <class Tuple, class = enable_if_t<tuple_like_v<Tuple>> >
    constexpr tuple_impl& operator=(Tuple &&t) {
        ((static_cast<tuple_leaf<Idx, Ts>&>(*this) =
            stl::forward< tuple_element_t<Idx, make_tuple_types_t<Tuple>> >(get<Idx>(t))
        ), ...);
        return *this;
    }

    constexpr tuple_impl& operator=(const tuple_impl &t) {
        ((static_cast<tuple_leaf<Idx, Ts>&>(*this) =
            static_cast<const tuple_leaf<Idx, Ts>&>(t).get()
        ), ...);
        return *this;
    }

    constexpr void swap(tuple_impl &t) {
        ((tuple_leaf<Idx, Ts>::swap(static_cast<tuple_leaf<Idx, Ts>&>(t))), ...);
    }

};

}} // namespace stl::detail

#endif // UTILITY_DETAIL_TUPLE
