#ifndef META_BITS_CONVERTIBLE
#define META_BITS_CONVERTIBLE

#include "meta/bits/constant.hpp"
#include "meta/bits/declval.hpp"

namespace stl {

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

template <class T, class U>
constexpr inline bool is_convertible_v = is_convertible<T, U>::value;

} // namespace stl

#endif // META_BITS_CONVERTIBLE
