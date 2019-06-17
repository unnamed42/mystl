#ifndef UTILITY_COMPARE
#define UTILITY_COMPARE

#include "meta/sfinae.hpp"
#include "utility/declval.hpp"

namespace stl {

namespace detail {
    template <class T, class U>
    using use_compare = decltype(declval<T>().compare(declval<U>()));

    template <class T, class U>
    using use_substract = decltype(declval<T>() - declval<U>());

    template <class T, class U>
    constexpr inline bool can_compare = is_detected_v<use_compare, T, U>;

    template <class T, class U>
    constexpr inline bool can_substract = is_detected_v<use_substract, T, U>;
} // namespace detail

template <class T1, class T2>
int compare(T1 &&t1, T2 &&t2) {
    if constexpr(detail::can_compare<T1, T2>)
        return t1.compare(t2);
    else if constexpr(detail::can_substract<T1, T2>)
        return t1 - t2;
    else {
        if(t1 < t2) return -1;
        if(t1 == t2) return 0;
        return 1;
    }
}

} // namespace stl

#endif // UTILITY_COMPARE
