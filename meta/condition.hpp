#ifndef META_CONDITION
#define META_CONDITION

#include "meta/base.hpp"

namespace stl {

template <bool B, class T, class F>
struct condition { using type = T; };

template <class T, class F>
struct condition<false, T, F> { using type = F; };

template <bool B, class T, class F>
using condition_t = typename stl::condition<B, T, F>::type;

template <class B>
struct not_
    : stl::constant<bool, !static_cast<bool>(B::value)> {};

template <class...> struct or_ : stl::false_type {};
template <class B1> struct or_<B1> : B1 {};
template <class B1, class ...Bn> struct or_<B1, Bn...>
    : stl::condition_t<static_cast<bool>(B1::value), B1, or_<Bn...>> {};

template <class...> struct and_ : stl::false_type {};
template <class B1> struct and_<B1> : B1 {};
template <class B1, class ...Bn> struct and_<B1, Bn...>
    : stl::condition_t<static_cast<bool>(B1::value), and_<Bn...>, B1> {};

} // namespace stl

#endif // META_CONDITION
