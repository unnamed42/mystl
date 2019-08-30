#ifndef META_BITS_NTH_ELEMENT
#define META_BITS_NTH_ELEMENT

#include "meta/bits/constant.hpp"
#include "meta/bits/identity.hpp"

namespace stl {

template <size_t, class> struct nth_element;

// for index sequence and alike

template <size_t I, template <class T, T...> class Sequence, class T, T first, T ...args>
struct nth_element<I, Sequence<T, first, args...>>
    : nth_element<I - 1, Sequence<T, args...>> {};

template <template <class T, T...> class Sequence, class T, T first, T ...args>
struct nth_element<0, Sequence<T, first, args...>>
    : constant<T, first> {};

template <size_t I, template <class T, T...> class Sequence, class T>
struct nth_element<I, Sequence<T>> {};

// for type sequence and alike

template <size_t I, template <class...> class Sequence, class First, class ...Args>
struct nth_element<I, Sequence<First, Args...>>
    : nth_element<I - 1, Sequence<Args...>> {};

template <template <class...> class Sequence, class First, class ...Args>
struct nth_element<0, Sequence<First, Args...>>
    : identity<First> {};

template <size_t I, template <class...> class Sequence>
struct nth_element<I, Sequence<>> {};

} // namespace stl

#endif // META_BITS_NTH_ELEMENT
