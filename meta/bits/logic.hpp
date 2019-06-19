#ifndef META_BITS_LOGIC
#define META_BITS_LOGIC

#include "meta/bits/constant.hpp"
#include "meta/bits/condition.hpp"

namespace stl {

template <class B>
struct not_ : boolean<!B::value> {};

template <class...> struct or_ : false_type {};
template <class B1> struct or_<B1> : B1 {};
template <class B1, class ...Bn> struct or_<B1, Bn...>
    : condition_t<static_cast<bool>(B1::value), B1, or_<Bn...>> {};

template <class...> struct and_ : false_type {};
template <class B1> struct and_<B1> : B1 {};
template <class B1, class ...Bn> struct and_<B1, Bn...>
    : condition_t<static_cast<bool>(B1::value), and_<Bn...>, B1> {};

template <class B>
constexpr inline bool not_v = not_<B>::value;

template <class ...Ts>
constexpr inline bool or_v = or_<Ts...>::value;

template <class ...Ts>
constexpr inline bool and_v = and_<Ts...>::value;

} // namespace stl

#endif // META_BITS_LOGIC

