#ifndef UTILITY_AS_REVERSE
#define UTILITY_AS_REVERSE

#include "meta/ref.hpp"
#include "container/access.hpp"

namespace stl {

namespace detail {

template <class Container>
class reverse_wrapper {
    Container &cont;
public:
    reverse_wrapper(Container &cont) noexcept
        : cont(cont) {}

    auto begin() { return stl::rbegin(cont); }
    auto end()   { return stl::rend(cont); }

    auto cbegin() const { return stl::rbegin(cont); }
    auto cend()   const { return stl::rend(cont); }
};

} // namespace detail

template <class T>
detail::reverse_wrapper<stl::remove_reference_t<T>> as_reverse(T &t) {
    return { t };
}

} // namespace stl

#endif // UTILITY_AS_REVERSE
