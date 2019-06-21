#ifndef UTILITY_DETAIL_TUPLE_LIKE
#define UTILITY_DETAIL_TUPLE_LIKE

#include "meta/bits/constant.hpp"
#include "meta/bits/remove_cv.hpp"

namespace stl {

template <class...> class tuple;
template <class, size_t> class array;
template <class, class> class pair;

namespace detail {

    template <class T> struct tuple_like_impl : false_type {};

    template <class ...Ts>
    struct tuple_like_impl<tuple<Ts...>> : true_type {};

    template <class T, class U>
    struct tuple_like_impl<pair<T, U>> : true_type {};

    template <class T, size_t N>
    struct tuple_like_impl<array<T, N>> : true_type {};

} // namespace detail

template <class T>
struct tuple_like : detail::tuple_like_impl<remove_cv_t<T>> {};

template <class T>
constexpr inline bool tuple_like_v = tuple_like<T>::value;

} // namespace stl

#endif // UTILITY_DETAIL_TUPLE_LIKE
