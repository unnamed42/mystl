#ifndef META_BITS_IS_INVOCABLE
#define META_BITS_IS_INVOCABLE

#include "meta/bits/constant.hpp"
#include "meta/bits/void_t.hpp"

#include "functional/bits/invoke_result.hpp"

namespace stl {

namespace detail {

    template <class Void, class F, class ...Args>
    struct is_invocable_impl : false_type {};

    template <class F, class ...Args>
    struct is_invocable_impl<void_t<invoke_result_t<F, Args...>>, F, Args...>
        : true_type {};

} // namespace detail

template <class F, class ...Args>
struct is_invocable : detail::is_invocable_impl<void, F, Args...> {};

template <class F, class ...Args>
constexpr inline bool is_invocable_v = is_invocable<F, Args...>::value;

} // namespace stl

#endif // META_BITS_IS_INVOCABLE
