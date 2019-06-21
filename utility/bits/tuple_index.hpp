#ifndef UTILITY_BITS_TUPLE_INDEX
#define UTILITY_BITS_TUPLE_INDEX

#include "meta/bits/index_sequence.hpp"
#include "meta/bits/remove_reference.hpp"

#include "utility/bits/tuple_size.hpp"

namespace stl {

template <class Tuple>
struct tuple_index
    : make_index_sequence<tuple_size_v<remove_reference_t<Tuple>>> {};

template <class Tuple>
using tuple_index_t = typename tuple_index<Tuple>::type;

} // namespace stl

#endif // UTILITY_BITS_TUPLE_INDEX
