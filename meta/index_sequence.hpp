#ifndef META_INDEX_SEQUENCE
#define META_INDEX_SEQUENCE

#include "def.hpp"

namespace stl {

// log(N) complexity solution from https://stackoverflow.com/a/17426611

template <size_t...> struct index_sequence {
    using type = index_sequence;
};

namespace detail {
    template <class A, class B> struct numbers_concat {};

    template <size_t ...I1, size_t ...I2>
    struct numbers_concat<index_sequence<I1...>, index_sequence<I2...>> {
        using type = index_sequence<I1..., (sizeof...(I1) + I2)...>;
    };
} // namespace detail

template <size_t N>
struct make_index_sequence : detail::numbers_concat<
    typename make_index_sequence<N/2>::type,
    typename make_index_sequence<N-N/2>::type
> {};

template <> struct make_index_sequence<0> : index_sequence<> {};
template <> struct make_index_sequence<1> : index_sequence<0> {};

template <size_t N>
using make_index_sequence_t = typename make_index_sequence<N>::type;

} // namespace stl

#endif // META_INDEX_SEQUENCE
