#ifndef FUNCTIONAL_BITS_APPLY
#define FUNCTIONAL_BITS_APPLY

#include "def.hpp"

#include "utility/bits/forward.hpp"
#include "utility/bits/get_fwd.hpp"
#include "utility/bits/detail/tuple_index.hpp"

#include "functional/bits/invoke.hpp"

namespace stl {

namespace detail {

    template <class F, class Tuple, size_t ...Idx>
    constexpr decltype(auto) apply_impl(F &&f, Tuple &&tuple, index_sequence<Idx...>) {
        return invoke(forward<F>(f), get<Idx>(forward<Tuple>(tuple))...);
    }

} // namespace detail

template <class F, class Tuple>
constexpr decltype(auto) apply(F &&f, Tuple &&tuple) {
    return detail::apply_impl(forward<F>(f), forward<Tuple>(tuple),
                              detail::tuple_index_t<Tuple>{});
}

} // namespace stl

#endif // FUNCTIONAL_BITS_APPLY
