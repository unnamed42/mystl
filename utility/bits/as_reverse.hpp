#ifndef UTILITY_BITS_aAS_REVERSE
#define UTILITY_BITS_aAS_REVERSE

#include "meta/bits/remove_reference.hpp"

#include "container/access.hpp"

namespace stl {

namespace detail {

template <class Container>
class reverse_wrapper {
    Container &cont;
public:
    constexpr reverse_wrapper(Container &cont) noexcept
        : cont(cont) {}

    constexpr auto begin() { return rbegin(cont); }
    constexpr auto end()   { return rend(cont); }

    constexpr auto cbegin() const { return rbegin(cont); }
    constexpr auto cend()   const { return rend(cont); }
};

} // namespace detail

template <class T>
constexpr detail::reverse_wrapper<remove_reference_t<T>> as_reverse(T &t) {
    return { t };
}

} // namespace stl

#endif // UTILITY_BITS_aAS_REVERSE
