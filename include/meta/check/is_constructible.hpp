#ifndef META_IS_CONSTRUCTIBLE
#define META_IS_CONSTRUCTIBLE

#include "meta/op/declval.hpp"
#include "meta/sfinae/is_detected.hpp"

namespace stl::meta {

namespace detail {

    template <class T, class ...Args>
    using construct = decltype(T(declval<Args>()...));

} // namespace detail

template <class T, class ...Args>
struct is_constructible : is_detected<detail::construct, T, Args...> {};

} // namespace stl::meta

#endif // META_IS_CONSTRUCTIBLE
