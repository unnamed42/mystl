#ifndef UTILITY_TUPLE_TYPES
#define UTILITY_TUPLE_TYPES

#include "def.hpp"

#include "meta/bits/identity.hpp"
#include "meta/bits/sequence.hpp"
#include "meta/bits/remove_cvref.hpp"
#include "meta/bits/is_reference.hpp"
#include "meta/bits/condition.hpp"

#include "utility/bits/tuple_size.hpp"
#include "utility/bits/tuple_element.hpp"

namespace stl {

template <class...> class tuple;

namespace detail {

    template <class Tuple>
    struct get_tuple_types_impl;

    template <class ...Ts>
    struct get_tuple_types_impl<tuple<Ts...>>
        : identity<types<Ts...>> {};

    template <class TupleTypes, class Tuple, size_t Start, size_t Stop>
    struct make_tuple_types_impl;

    template <class ...Ts, class Tuple, size_t Start, size_t Stop>
    struct make_tuple_types_impl<types<Ts...>, Tuple, Start, Stop>
        : make_tuple_types_impl<
              types<Ts..., condition_t<is_lvalue_reference_v<Tuple>,
                    // maintain reference-ness
                    tuple_element_t<Start, remove_reference_t<Tuple>>&,
                    tuple_element_t<Start, remove_reference_t<Tuple>> >
                   >,
              Tuple, Start + 1, Stop> {};

    template <class ...Ts, class Tuple, size_t Stop>
    struct make_tuple_types_impl<types<Ts...>, Tuple, Stop, Stop>
        : identity<types<Ts...>> {};

} // namespace detail

template <class Tuple>
struct get_tuple_types
    : detail::get_tuple_types_impl<remove_cvref_t<Tuple>> {};

// make_tuple_types

template <class Tuple,
          size_t Stop = tuple_size_v<remove_reference_t<Tuple>>,
          size_t Start = 0>
struct make_tuple_types {
    static_assert(Stop >= Start, "make_tuple_types: invalid start index");

    using type = typename detail::make_tuple_types_impl<
        types<>, Tuple, Start, Stop
    >::type;
};

template <class Tuple,
          size_t Stop = tuple_size_v<remove_reference_t<Tuple>>,
          size_t Start = 0>
using make_tuple_types_t = typename make_tuple_types<Tuple, Stop, Start>::type;

} // namespace stl

#endif // UTILITY_TUPLE_TYPES
