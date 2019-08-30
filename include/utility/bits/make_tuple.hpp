#ifndef UTILITY_BITS_MAKE_TUPLE
#define UTILITY_BITS_MAKE_TUPLE

#include "meta/bits/identity.hpp"
#include "meta/bits/decay.hpp"

#include "utility/tuple.hpp"
#include "utility/bits/forward.hpp"

namespace stl {

template <class> class reference_wrapper;

namespace detail {

    template <class T>
    struct unwrap_refwrapper : identity<T> {};

    template <class T>
    struct unwrap_refwrapper<reference_wrapper<T>> : identity<T&> {};

    template <class T>
    using special_decay_t = typename unwrap_refwrapper<decay_t<T>>::type;

} // namespace detail

template <class ...Ts>
constexpr auto make_tuple(Ts&& ...ts) {
    return tuple<detail::special_decay_t<Ts>...>(forward<Ts>(ts)...);
}

template <class ...Ts>
constexpr tuple<Ts&&...> forward_as_tuple(Ts&& ...ts) noexcept {
    return tuple<Ts&&...>(forward<Ts>(ts)...);
}

} // namespace stl

#endif // UTILITY_BITS_MAKE_TUPLE
