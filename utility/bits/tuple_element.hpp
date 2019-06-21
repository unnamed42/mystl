#ifndef UTILITY_DETAIL_TUPLE_ELEMENT
#define UTILITY_DETAIL_TUPLE_ELEMENT

#include "def.hpp"

#include "meta/bits/identity.hpp"
#include "meta/bits/nth_element.hpp"
#include "meta/bits/copy_cv.hpp"
#include "meta/bits/remove_cv.hpp"

namespace stl {

template <class...> class tuple;
template <class, class> class pair;
template <class, size_t> class array;

template <class...> struct tuple_types;

namespace detail {

    template <size_t, class>
    struct tuple_element_impl;

    // specialization for tuple_types

    template <size_t I, class ...Ts>
    struct tuple_element_impl<I, tuple_types<Ts...>>
        : nth_element<I, tuple_types<Ts...>> {};

    // specialization for tuple

    template <size_t I, class ...Ts>
    struct tuple_element_impl<I, tuple<Ts...>>
        : tuple_element_impl<I, tuple_types<Ts...>> {};

    // specialization for pair

    template <class T, class U>
    struct tuple_element_impl<0, pair<T, U>>
        : identity<T> {};

    template <class T, class U>
    struct tuple_element_impl<1, pair<T, U>>
        : identity<U> {};

    // specialization for array

    template <size_t I, class T, size_t N>
    struct tuple_element_impl<I, array<T, N>>
        : identity<T> {
        static_assert(I < N, "tuple_element: array index out of bounds");
    };

} // namespace detail

template <size_t I, class T>
struct tuple_element : copy_cv<
    typename detail::tuple_element_impl<I, remove_cv_t<T>>::type,
    T
> {};

template <size_t I, class T>
using tuple_element_t = typename tuple_element<I, T>::type;

} // namespace stl

#endif // UTILITY_DETAIL_TUPLE_ELEMENT
