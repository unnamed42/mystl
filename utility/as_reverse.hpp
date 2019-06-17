#ifndef UTILITY_AS_REVERSE
#define UTILITY_AS_REVERSE

#include "meta/cvref.hpp"

#include "container/access.hpp"

namespace stl {

namespace detail {

template <class Container>
class reverse_wrapper {
    Container &cont;
public:
    reverse_wrapper(Container &cont) noexcept
        : cont(cont) {}

    auto begin() { return rbegin(cont); }
    auto end()   { return rend(cont); }

    auto cbegin() const { return rbegin(cont); }
    auto cend()   const { return rend(cont); }
};

} // namespace detail

template <class T>
detail::reverse_wrapper<remove_reference_t<T>> as_reverse(T &t) {
    return { t };
}

} // namespace stl

#endif // UTILITY_AS_REVERSE
