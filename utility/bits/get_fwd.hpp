#ifndef UTILITY_BITS_GET_FWD
#define UTILITY_BITS_GET_FWD

#include "def.hpp"

#include "meta/bits/remove_cvref.hpp"

#include "utility/bits/forward.hpp"

namespace stl {

namespace detail {

    template <class T> struct get_impl;

} // namespace detail

template <size_t I, class Tuple>
inline constexpr decltype(auto) get(Tuple &&t) {
    return detail::get_impl<remove_cvref_t<Tuple>>
                 ::template get<I>(forward<Tuple>(t));
}

} // namespace stl

#endif // UTILITY_BITS_GET_FWD
