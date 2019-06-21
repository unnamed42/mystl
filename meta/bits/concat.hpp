#ifndef META_BITS_CONCAT
#define META_BITS_CONCAT

#include "meta/bits/identity.hpp"

namespace stl {

template <class, class> struct concat;

template <template <class...> class Sequence, class ...Ts, class ...Us>
struct concat<Sequence<Ts...>, Sequence<Us...>>
    : identity<Sequence<Ts..., Us...>> {};

template <template <class T, T...> class Sequence, class T, T ...args1, T ...args2>
struct concat<Sequence<T, args1...>, Sequence<T, args2...>>
    : identity<Sequence<T, args1..., args2...>> {};

} // namespace stl

#endif // META_BITS_CONCAT
