#ifndef UTILITY_TUPLE_TRAITS
#define UTILITY_TUPLE_TRAITS

#include "meta/cv.hpp"

namespace stl {

template <class...> struct tuple;
template <class...> struct tuple_types {};

namespace detail {

    template <class>
    struct tuple_size;

    template <class ...Ts>
    struct tuple_size<tuple_types<Ts...>
        : constant<size_t, sizeof...(Ts)> {};

    template <class ...Ts>
    struct tuple_size<tuple<Ts...>>
        : constant<size_t, sizeof...(Ts)> {};

    template <size_t I, class T>
    struct tuple_element;

    template <size_t I>
    struct tuple_element<I, tuple_types<>> {
        static_assert(false, "tuple_element index out of range");
    };

    template <class First, class ...Ts>
    struct tuple_element<0, tuple_types<First, Ts...>> {
        using type = First;
    };

    template <size_t I, class First, class ...Ts>
    struct tuple_element<I, tuple_types<First, Ts...>> {
        using type = typename tuple_element<I - 1, tuple_types<Ts...>>::type;
    };

    template <size_t I, class ...Ts>
    struct tuple_element<I, tuple<Ts...>> {
        using type = typename tuple_element<I, tuple_types<Ts...>>::type;
    };

    template <size_t I, class ...Ts>
    struct tuple_element<I, const tuple<Ts...>> {
        using type = add_const_t<typename tuple_element<I, tuple_types<Ts...>::type>;
    };

    template <size_t I, class ...Ts>
    struct tuple_element<I, volatile tuple<Ts...>> {
        using type = add_volatile_t<typename tuple_element<I, tuple_types<Ts...>::type>;
    };

    template <size_t I, class ...Ts>
    struct tuple_element<I, const volatile tuple<Ts...>> {
        using type = add_const_t<
                        add_volatile_t<
                            typename tuple_element<I, tuple_types<Ts...>::type
                        >
                     >;
    };

} // namespace detail

template <class T>
struct tuple_size
    : detail::tuple_size<remove_cv_t<T>> {};

template <size_t I, class T>
struct tuple_element : detail::tuple_element<I, T> {};

} // namespace stl

#endif // UTILITY_TUPLE_ELEMENTS
