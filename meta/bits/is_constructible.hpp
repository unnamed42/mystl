#ifndef META_BITS_CONSTRUCTIBLE
#define META_BITS_CONSTRUCTIBLE

#include "meta/bits/constant.hpp"
#include "meta/bits/void_t.hpp"
#include "meta/bits/declval.hpp"

namespace stl {

namespace detail {

    template <class, class, class...>
    struct is_constructible : false_type {};

    template <class T, class ...Args>
    struct is_constructible<
        void_t<decltype(T(declval<Args>()...))>,
        T, Args...
    > : true_type {};

} // namespace detail

template <class T, class ...Args>
struct is_constructible : detail::is_constructible<void_t<>, T, Args...> {};

template <class T, class ...Args>
constexpr inline bool is_constructible_v = is_constructible<T, Args...>::value;

} // namespace stl

#endif // META_BITS_CONSTRUCTIBLE
