#ifndef UTILITY_FORWARD
#define UTILITY_FORWARD

#include "meta/bits/remove_reference.hpp"

namespace stl {

template <class T>
constexpr remove_reference_t<T>&& move(T &&t) noexcept {
    return static_cast<remove_reference_t<T>&&>(t);
}

template <class T>
constexpr T&& forward(remove_reference_t<T> &arg) noexcept {
    return static_cast<T&&>(arg);
}

template <class T>
constexpr T&& forward(remove_reference_t<T> &&arg) noexcept {
    return static_cast<T&&>(arg);
}

} // namespace stl

#endif // UTILITY_FORWARD
