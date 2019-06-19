#ifndef UTILITY_DETAIL_TUPLE_ELEMENT
#define UTILITY_DETAIL_TUPLE_ELEMENT

#include "def.hpp"

#include "meta/bits/identity.hpp"
#include "meta/bits/add_cv.hpp"

namespace stl {

template <class...> class tuple;
template <class...> struct tuple_types;

template <size_t I, class T>
struct tuple_element;

template <size_t I>
struct tuple_element<I, tuple_types<>> {
    static_assert(I != I, "tuple_element index out of range");
};

template <class First, class ...Ts>
struct tuple_element<0, tuple_types<First, Ts...>>
    : identity<First> {};

template <size_t I, class First, class ...Ts>
struct tuple_element<I, tuple_types<First, Ts...>>
    : tuple_element<I - 1, tuple_types<Ts...>> {};

// specializations for tuple
template <size_t I, class ...Ts>
struct tuple_element<I, tuple<Ts...>>
    : tuple_element<I, tuple_types<Ts...>> {};

template <size_t I, class ...Ts>
struct tuple_element<I, const tuple<Ts...>>
    : add_const< typename tuple_element<I, tuple_types<Ts...>>::type > {};

template <size_t I, class ...Ts>
struct tuple_element<I, volatile tuple<Ts...>>
    : add_volatile< typename tuple_element<I, tuple_types<Ts...>>::type > {};

template <size_t I, class ...Ts>
struct tuple_element<I, const volatile tuple<Ts...>>
    : add_cv< typename tuple_element<I, tuple_types<Ts...>>::type > {};

template <size_t I, class T>
using tuple_element_t = typename tuple_element<I, T>::type;

} // namespace stl

#endif // UTILITY_DETAIL_TUPLE_ELEMENT
