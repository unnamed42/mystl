#ifndef UTILITY_FORWARD
#define UTILITY_FORWARD

#include "meta/ref.hpp"

namespace rubbish {

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

template <class T>
add_rvalue_reference_t<T> declval() noexcept;

} // namespace rubbish

#endif // UTILITY_FORWARD
