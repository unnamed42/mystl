#ifndef META_LOGIC
#define META_LOGIC

#include "meta/base/constant.hpp"
#include "meta/op/condition.hpp"

namespace stl::meta {

template <class B>
struct not_ : boolean<!B::value> {};

template <class...> struct or_;
template <class B1> struct or_<B1> : B1 {};
template <class B1, class ...Bn> struct or_<B1, Bn...>
    : condition_t<static_cast<bool>(B1::value), B1, or_<Bn...>> {};

template <class...> struct and_;
template <class B1> struct and_<B1> : B1 {};
template <class B1, class ...Bn> struct and_<B1, Bn...>
    : condition_t<static_cast<bool>(B1::value), and_<Bn...>, B1> {};

} // namespace stl::meta

#endif // META_LOGIC

