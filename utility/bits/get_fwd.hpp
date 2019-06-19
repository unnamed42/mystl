#ifndef UTILITY_BITS_GET_FWD
#define UTILITY_BITS_GET_FWD

#include "utility/bits/tuple_element.hpp"

namespace stl {

template <class...> class tuple;

template <size_t I, class ...Ts>
inline tuple_element_t<I, tuple<Ts...>>& get(tuple<Ts...> &t);

template <size_t I, class ...Ts>
inline tuple_element_t<I, tuple<Ts...>>&& get(tuple<Ts...> &&t);

template <size_t I, class ...Ts>
inline const tuple_element_t<I, tuple<Ts...>>& get(const tuple<Ts...> &t);

} // namespace stl

#endif // UTILITY_BITS_GET_FWD
