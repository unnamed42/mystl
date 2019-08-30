#ifndef META_BITS_CONCAT
#define META_BITS_CONCAT

#include "meta/bits/identity.hpp"

namespace stl {

namespace detail {

    template <class, class> struct concat_two;

    template <template <class...> class Sequence, class ...Ts, class ...Us>
    struct concat_two<Sequence<Ts...>, Sequence<Us...>>
        : identity<Sequence<Ts..., Us...>> {};

} // namespace detail

template <class...> struct concat;

template <class Seq> struct concat<Seq> : identity<Seq> {};

template <template <class...> class Seq, class... Ts, class... Rest>
struct concat<Seq<Ts...>, Rest...>
    : detail::concat_two<Seq<Ts...>, typename concat<Rest...>::type> {
};

} // namespace stl

#endif // META_BITS_CONCAT
