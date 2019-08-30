#ifndef CRTP_RANGE_ACCESS
#define CRTP_RANGE_ACCESS

#include "iterator/const_iterator.hpp"
#include "iterator/reverse_iterator.hpp"

namespace stl {

template <class Derived, class Iterator>
class range_access {
private:
    using const_iterator   = stl::const_iterator<Iterator>;
    using reverse_iterator = stl::reverse_iterator<Iterator>;
    using const_reverse_iterator = stl::const_iterator<reverse_iterator>;

    constexpr       Derived& derived()       noexcept { return *static_cast<Derived*>(this); }
    constexpr const Derived& derived() const noexcept { return *static_cast<const Derived*>(this); }
public:
    constexpr const_iterator cbegin() const { return const_iterator{derived().begin()}; }
    constexpr const_iterator cend()   const { return const_iterator{derived().end()}; }

    constexpr reverse_iterator rbegin() { return reverse_iterator{derived().end()}; }
    constexpr reverse_iterator rend()   { return reverse_iterator{derived().begin()}; }

    constexpr const_reverse_iterator crbegin() const { return const_iterator{rbegin()}; }
    constexpr const_reverse_iterator crend()   const { return const_iterator{rend}; }
};

} // namespace stl

#endif // CRTP_RANGE_ACCESS
