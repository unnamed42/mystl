#ifndef UTILITY_DETAIL_TUPLE_SIZE
#define UTILITY_DETAIL_TUPLE_SIZE

#include "def.hpp"

#include "meta/bits/constant.hpp"
#include "meta/bits/remove_cv.hpp"
#include "meta/bits/remove_reference.hpp"

namespace stl {

template <class...> class tuple;
template <class, class> class pair;
template <class, size_t> class array;

template <class...> struct tuple_types;

namespace detail {

    template <class>
    struct tuple_size_impl {};

    template <class ...Ts>
    struct tuple_size_impl<tuple_types<Ts...>>
        : constant<size_t, sizeof...(Ts)> {};

    template <class ...Ts>
    struct tuple_size_impl<tuple<Ts...>>
        : constant<size_t, sizeof...(Ts)> {};

    template <class T, class U>
    struct tuple_size_impl<pair<T, U>>
        : constant<size_t, 2> {};

    template <class T, size_t N>
    struct tuple_size_impl<array<T, N>>
        : constant<size_t, N> {};

} // namespace detail

template <class T>
struct tuple_size : detail::tuple_size_impl<remove_cv_t<T>> {};

template <class T>
constexpr inline size_t tuple_size_v = tuple_size<T>::value;

template <class T, class U>
struct tuple_same_size
    : boolean< tuple_size_v<remove_reference_t<T>> == tuple_size_v<remove_reference_t<U>> > {};

template <class T, class U>
constexpr inline bool tuple_same_size_v = tuple_same_size<T, U>::value;

} // namespace stl

#endif // UTILITY_DETAIL_TUPLE_SIZE
