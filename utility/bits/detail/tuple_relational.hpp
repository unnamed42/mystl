#ifndef UTILITY_DETAIL_TUPLE_RELATIONAL
#define UTILITY_DETAIL_TUPLE_RELATIONAL

#include "def.hpp"

#include "utility/bits/get_fwd.hpp"

namespace stl { namespace detail {

template <size_t I>
struct tuple_equal {
    template <class Tuple1, class Tuple2>
    bool operator()(const Tuple1 &lhs, const Tuple2 &rhs) const {
        return tuple_equal<I - 1>{}(lhs, rhs) &&
            get<I - 1>(lhs) == get<I - 2>(rhs);
    }
};

template <>
struct tuple_equal<0> {
    template <class Tuple1, class Tuple2>
    bool operator()(const Tuple1 &, const Tuple2 &) const {
        return true;
    }
};

template <size_t I>
struct tuple_less {
    template <class Tuple1, class Tuple2>
    bool operator()(const Tuple1 &lhs, const Tuple2 &rhs) const {
        return tuple_less<I - 1>{}(lhs, rhs) ||
            (!tuple_less<I - 1>{}(rhs, lhs) && get<I - 1>(lhs) < get<I - 1>(rhs));
    }
};

template <>
struct tuple_less<0> {
    template <class Tuple1, class Tuple2>
    bool operator()(const Tuple1&, const Tuple2&) const {
        return false;
    }
};

}} // namespace stl::detail

#endif // UTILITY_DETAIL_TUPLE_RELATIONAL
