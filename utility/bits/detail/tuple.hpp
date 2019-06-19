#ifndef UTILITY_DETAIL_TUPLE
#define UTILITY_DETAIL_TUPLE

#include "def.hpp"

#include "meta/bits/index_sequence.hpp"

#include "utility/bits/forward.hpp"
#include "utility/bits/get_fwd.hpp"
#include "utility/bits/tuple_types.hpp"
#include "utility/bits/pack_expansion.hpp"
#include "utility/bits/tuple_element.hpp"
#include "utility/bits/tuple_types.hpp"
#include "utility/bits/detail/tuple_leaf.hpp"

namespace stl { namespace detail {

template <class Idx, class ...Ts> struct tuple;

template <size_t ...Idx, class ...Ts>
struct tuple<index_sequence<Idx...>, Ts...> : tuple_leaf<Idx, Ts>... {

    template <size_t ...Idx1, class ...Ts1,
              size_t ...Idx2, class ...Ts2, class ...Values>
    explicit tuple(index_sequence<Idx1...>, tuple_types<Ts1...>,
                   index_sequence<Idx2...>, tuple_types<Ts2...>, Values&& ...values)
        : tuple_leaf<Idx1, Ts1>(stl::forward<Values>(values))...,
          tuple_leaf<Idx2, Ts2>()... {}

    template <class Tuple>
    tuple(Tuple &&tuple) : tuple_leaf<Idx, Ts> (
        stl::forward< tuple_element_t<Idx, make_tuple_types_t<Tuple>> >(get<Idx>(tuple))
    )... {}

    template <class Tuple>
    tuple& operator=(Tuple &&tuple) {
        CALL_ON_PACK((static_cast<tuple_leaf<Idx, Ts>&>(*this) =
            stl::forward< tuple_element_t<Idx, make_tuple_types_t<Tuple>> >(get<Idx>(tuple))
        ));
        return *this;
    }

    tuple& operator=(const tuple &tuple) {
        CALL_ON_PACK((static_cast<tuple_leaf<Idx, Ts>&>(*this) =
            static_cast<const tuple_leaf<Idx, Ts>&>(tuple).get()
        ));
        return *this;
    }

    void swap(tuple &tuple) {
        CALL_ON_PACK((tuple_leaf<Idx, Ts>::swap(
            static_cast<tuple_leaf<Idx, Ts>&>(tuple))
        ));
    }

};

}} // namespace stl::detail

#endif // UTILITY_DETAIL_TUPLE
