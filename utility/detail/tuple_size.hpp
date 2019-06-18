#ifndef UTILITY_DETAIL_TUPLE_SIZE
#define UTILITY_DETAIL_TUPLE_SIZE

namespace stl {

template <class...> struct tuple;
template <class...> struct tuple_types;

namespace detail {

    template <class>
    struct tuple_size;

    template <class ...Ts>
    struct tuple_size<tuple_types<Ts...>>
        : constant<size_t, sizeof...(Ts)> {};

    template <class ...Ts>
    struct tuple_size<tuple<Ts...>>
        : constant<size_t, sizeof...(Ts)> {};

} // namespace detail

template <class T>
struct tuple_size : detail::tuple_size<remove_cv_t<T>> {};

template <class T>
constexpr inline size_t tuple_size_v = tuple_size<T>::value;

} // namespace stl

#endif // UTILITY_DETAIL_TUPLE_SIZE
