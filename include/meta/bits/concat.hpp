#ifndef META_BITS_CONCAT
#define META_BITS_CONCAT

#include "meta/bits/identity.hpp"

namespace stl {

namespace detail {

    template <class, class> struct concat_two;

    template <template <class...> class Sequence, class ...Ts, class ...Us>
    struct concat_two<Sequence<Ts...>, Sequence<Us...>>
        : identity<Sequence<Ts..., Us...>> {};

    template <template <class T, T...> class Sequence, class T, T ...args1, T ...args2>
    struct concat_two<Sequence<T, args1...>, Sequence<T, args2...>>
        : identity<Sequence<T, args1..., args2...>> {};

} // namespace detail



template <class A, class B>
struct concat_lazy : concat<typename A::type,
                            typename B::type> {};

} // namespace stl

#endif // META_BITS_CONCAT
