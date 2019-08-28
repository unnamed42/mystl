#ifndef META_IS_CONVERTIBLE
#define META_IS_CONVERTIBLE

#include "meta/op/declval.hpp"
#include "meta/base/constant.hpp"

namespace stl::meta {

namespace detail {

    struct is_convertible_h {
        template <class T, class U>
        static void convert(U);

        template <class T, class U>
        static auto test(T&&, U&&)
            -> decltype(convert<T, U>(declval<T>()), true_type{});

        static auto test(...) -> false_type;
    };

} // namespace detail

template <class T, class U>
struct is_convertible
    : decltype(detail::is_convertible_h::test(declval<T>(), declval<U>())) {};

} // namespace stl::meta

#endif // META_IS_CONVERTIBLE
