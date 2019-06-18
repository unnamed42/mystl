#ifndef UTILITY_DETAIL_TUPLE
#define UTILITY_DETAIL_TUPLE

#include "def.hpp"

#include "meta/index_sequence.hpp"

#include "utility/forward.hpp"
#include "utility/tuple_types.hpp"
#include "utility/detail/pack_expansion.hpp"
#include "utility/detail/tuple_element.hpp"
#include "utility/detail/tuple_types.hpp"
#include "utility/detail/detail_tuple_leaf.hpp"

namespace stl { namespace detail {

template <class Indexes, class ...Ts>
struct tuple;

template <size_t I, class C>
decltype(auto) get(C&&);

template <size_t ...Indexes, class ...Ts>
struct tuple<index_sequence<Indexes...>, Ts...>
    : tuple_leaf<Indexes, Ts>... {

    template <size_t ...Indexes1, class ...Ts1,
              size_t ...Indexes2, class ...Ts2,
              class ...Args>
    explicit tuple(
        index_sequence<Indexes1...>, tuple_types<Ts1...>,
        index_sequence<Indexes2...>, tuple_types<Ts2...>,
        Args&& ...values)
        : tuple_leaf<Indexes1, Ts1>(forward<Args>(values))...,
          tuple_leaf<Indexes2, Ts2>()... {}

    template <class Tuple>
    tuple(Tuple &&tuple)
        : tuple_leaf<Indexes, Ts>(
            forward< tuple_element_t<Indexes, make_tuple_types_t<Tuple>> >(get<Indexes>(tuple))
          )... {}

    template <class Tuple>
    tuple& operator=(Tuple &&tuple) {
        CALL_ON_PACK((static_cast<tuple_leaf<Indexes, Ts>&>(*this) =
            forward< tuple_element_t<Indexes, make_tuple_types_t<Tuple>> >(get<Indexes>(tuple))
        ));
        return *this;
    }

    tuple& operator=(const tuple &tuple) {
        CALL_ON_PACK((static_cast<tuple_leaf<Indexes, Ts>&>(*this) =
            static_cast<const tuple_leaf<Indexes, Ts>&>(tuple).get()
        ));
        return *this;
    }

    void swap(tuple &tuple) {
        CALL_ON_PACK((tuple_leaf<Indexes, Ts>::swap(
            static_cast<tuple_leaf<Indexes, Ts>&>(tuple))
        ));
    }

};

}} // namespace stl::detail

#endif // UTILITY_DETAIL_TUPLE
