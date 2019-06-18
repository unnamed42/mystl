#ifndef UTILITY_TUPLE_TYPES
#define UTILITY_TUPLE_TYPES

#include "def.hpp"

#include "meta/cvref.hpp"
#include "meta/check.hpp"
#include "meta/condition.hpp"

#include "utility/tuple_traits.hpp"
#include "utility/detail/tuple_size.hpp"
#include "utility/detail/tuple_element.hpp"

namespace stl {

template <class...> struct tuple_types {};

namespace detail {

    template <class TupleTypes, class Tuple, size_t Start, size_t Stop>
    struct make_tuple_types;

    template <class ...Ts, class Tuple, size_t Start, size_t Stop>
    struct make_tuple_types<tuple_types<Ts...>, Tuple, Start, Stop>
        : make_tuple_types<
              tuple_types<Ts..., condition_t<is_lvalue_reference_v<Tuple>,
                            // maintain reference-ness
                            tuple_element_t<Start, remove_reference_t<Tuple>>&,
                            tuple_element_t<Start, remove_reference_t<Tuple>> >
                         >,
              Tuple, Start + 1, Stop>::type {};

    template <class ...Ts, class Tuple, size_t Stop>
    struct make_tuple_types<tuple_types<Ts...>, Tuple, Stop, Stop>
        : identity<tuple_types<Ts...>> {};

} // namespace detail

template <class Tuple, size_t Start = 0,
          size_t Stop = tuple_size_v<remove_reference_t<Tuple>>>
struct make_tuple_types : detail::make_tuple_types<tuple_types<>, Tuple, Start, Stop> {
    static_assert(Start <= Stop, "make_tuple_types: invalid parameters");
};

template <class Tuple, size_t Start = 0,
          size_t Stop = tuple_size_v<remove_reference_t<Tuple>>>
using make_tuple_types_t = typename make_tuple_types<Tuple, Start, Stop>::type;

} // namespace stl

#endif // UTILITY_TUPLE_TYPES
