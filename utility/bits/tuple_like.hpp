#ifndef UTILITY_DETAIL_TUPLE_LIKE
#define UTILITY_DETAIL_TUPLE_LIKE

#include "meta/bits/constant.hpp"
#include "meta/bits/remove_cv.hpp"

namespace stl {

template <class...> struct tuple;

namespace detail {

    template <class T> struct tuple_like : false_type {};

    template <class ...Ts>
    struct tuple_like<tuple<Ts...>> : true_type {};

    // TODO: specializations for array, pair, std equivalences

} // namespace detail

template <class T>
struct tuple_like : detail::tuple_like<remove_cv_t<T>> {};

template <class T>
constexpr inline bool tuple_like_v = tuple_like<T>::value;

} // namespace stl

#endif // UTILITY_DETAIL_TUPLE_LIKE
