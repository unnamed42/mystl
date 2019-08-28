#ifndef ALGO_SENTINEL
#define ALGO_SENTINEL

#include "meta/op/declval.hpp"
#include "meta/op/logic.hpp"
#include "meta/sfinae/satisfied.hpp"
#include "meta/sfinae/is_detected.hpp"

namespace stl::algo::detail {

template <class A, class B>
using eq_compare = decltype(meta::declval<A>() == meta::declval<B>());

template <class A, class B>
using ne_compare = decltype(meta::declval<A>() != meta::declval<B>());

template <class Sentinel, class Iterator>
struct is_sentinel : meta::and_<
    meta::is_detected<eq_compare, Sentinel, Iterator>,
    meta::is_detected<eq_compare, Iterator, Sentinel>,
    meta::is_detected<ne_compare, Sentinel, Iterator>,
    meta::is_detected<ne_compare, Iterator, Sentinel>,
> {};

template <class Sentinel, class Iterator>
using sentinel = satisfied<is_sentinel, Sentinel, Iterator>;

} // namespace stl::algo::detail

#endif // ALGO_SENTINEL
