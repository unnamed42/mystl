#ifndef UTILITY_DETAIL_TUPLES_FOREACH
#define UTILITY_DETAIL_TUPLES_FOREACH

#include "meta/bits/constant.hpp"
#include "meta/bits/logic.hpp"
#include "meta/bits/remove_reference.hpp"

#include "utility/bits/tuple_size.hpp"
#include "utility/bits/tuple_like.hpp"
#include "utility/bits/tuple_types.hpp"

namespace stl {

namespace detail {

template <template <class...> class Binary, class TupleTypes1, class TupleTypes2>
struct tuples_foreach_impl : false_type {};

template <template <class...> class Binary>
struct tuples_foreach_impl< Binary, types<>, types<> > : true_type {};

template <template <class...> class Binary,
          class T, class ...Ts, class U, class ...Us>
struct tuples_foreach_impl< Binary, types<T, Ts...>, types<U, Us...> >
    : and_< Binary<T, U>, tuples_foreach_impl<Binary, types<Ts...>, types<Us...>> > {};

template <template <class...> class Binary,
          class Tuple1, class Tuple2,
          bool = and_v<tuple_like<remove_reference_t<Tuple1>>,
                       tuple_like<remove_reference_t<Tuple2>>,
                       tuple_same_size<Tuple1, Tuple2>
                      >
         >
struct tuples_foreach : false_type {};

template <template <class...> class Binary,
          class Tuple1, class Tuple2>
struct tuples_foreach<Binary, Tuple1, Tuple2, true>
    : tuples_foreach_impl<Binary,
        make_tuple_types_t<Tuple1>,
        make_tuple_types_t<Tuple2>> {};

} // namespace detail

} // namespace stl

#endif // UTILITY_DETAIL_TUPLES_FOREACH
