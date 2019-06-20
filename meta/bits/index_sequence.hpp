#ifndef META_BITS_INDEX_SEQUENCE
#define META_BITS_INDEX_SEQUENCE

#include "def.hpp"

#include "meta/bits/identity.hpp"

namespace stl {

// log(N) complexity solution from https://stackoverflow.com/a/17426611

template <size_t...> struct index_sequence {};

namespace detail {

    template <class A, class B> struct numbers_concat;

    template <size_t ...I1, size_t ...I2>
    struct numbers_concat<index_sequence<I1...>, index_sequence<I2...>>
        : identity<index_sequence<I1..., (sizeof...(I1) + I2)...>> {};

    template <class, size_t> struct index_sequence_add;

    template <size_t ...Idx, size_t N>
    struct index_sequence_add<index_sequence<Idx...>, N>
        : identity<index_sequence<(Idx + N)...>> {};

    template <size_t N>
    struct make_index_sequence_impl : numbers_concat<
        typename make_index_sequence_impl<N/2>::type,
        typename make_index_sequence_impl<N - N/2>::type
    > {};

    template <> struct make_index_sequence_impl<0> : identity<index_sequence<>> {};
    template <> struct make_index_sequence_impl<1> : identity<index_sequence<0>> {};

} // namespace detail

template <size_t Stop, size_t Start = 0>
struct make_index_sequence {
    static_assert(Stop >= Start, "make_index_sequence: invalid start index");

    using type = typename detail::index_sequence_add<
        typename detail::make_index_sequence_impl<Stop - Start>::type,
        Start
    >::type;
};

template <size_t N>
struct make_index_sequence<N, 0> : detail::make_index_sequence_impl<N> {};

template <size_t Stop, size_t Start = 0>
using make_index_sequence_t = typename make_index_sequence<Stop, Start>::type;

} // namespace stl

#endif // META_BITS_INDEX_SEQUENCE
