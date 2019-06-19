#ifndef UTILITY_DETAIL_TUPLE_CONVERTIBLE
#define UTILITY_DETAIL_TUPLE_CONVERTIBLE

#include "meta/bits/logic.hpp"
#include "meta/bits/constant.hpp"
#include "meta/bits/is_convertible.hpp"
#include "meta/bits/remove_reference.hpp"

#include "utility/detail/tuple_like.hpp"
#include "utility/detail/tuple_size.hpp"
#include "utility/detail/tuple_types.hpp"

namespace stl {

template <class...> struct tuple_types;

namespace detail {

    template <bool SameSize, class From, class To>
    struct tuple_convertible : false_type {};

    template <>
    struct tuple_convertible<true, tuple_types<>, tuple_types<>> : true_type {};

    template <class From, class ...Fs,
              class To  , class ...Ts>
    struct tuple_convertible<true,
                             tuple_types<From, Fs...>,
                             tuple_types<To  , Ts...>>
        : and_<is_convertible<From, To>, tuple_convertible<true,
                  tuple_types<Fs...>, tuple_types<Ts...>>
              > {};

} // namespace detail

template <class From, class To,
          bool = tuple_like_v<remove_reference_t<From>>,
          bool = tuple_like_v<remove_reference_t<To>> >
struct tuple_convertible : false_type {};

template <class From, class To>
struct tuple_convertible<From, To, true, true>
    : detail::tuple_convertible<
        tuple_size_v<remove_reference_t<From>> == tuple_size_v<remove_reference_t<To>>,
        make_tuple_types_t<From>,
        make_tuple_types_t<To>
    > {};

template <class F, class T,
          bool BF = tuple_like_v<remove_reference_t<F>>,
          bool BT = tuple_like_v<remove_reference_t<T>> >
constexpr inline bool tuple_convertible_v = tuple_convertible<F, T, BF, BT>::value;

} // namespace stl

#endif // UTILITY_DETAIL_TUPLE_CONVERTIBLE
