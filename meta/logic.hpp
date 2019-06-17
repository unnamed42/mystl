#ifndef META_LOGIC
#define META_LOGIC

#include "meta/base.hpp"
#include "meta/condition.hpp"

namespace stl {

template <class B>
struct not_
    : constant<bool, !static_cast<bool>(B::value)> {};

template <class...> struct or_ : false_type {};
template <class B1> struct or_<B1> : B1 {};
template <class B1, class ...Bn> struct or_<B1, Bn...>
    : condition_t<static_cast<bool>(B1::value), B1, or_<Bn...>> {};

template <class...> struct and_ : false_type {};
template <class B1> struct and_<B1> : B1 {};
template <class B1, class ...Bn> struct and_<B1, Bn...>
    : condition_t<static_cast<bool>(B1::value), and_<Bn...>, B1> {};

} // namespace stl

#endif // META_LOGIC
