#ifndef RANGE_ACCESS
#define RANGE_ACCESS

#include "iterator/const_iterator.hpp"
#include "iterator/reverse_iterator.hpp"

namespace rubbish {

template <class Derived>
class range_access {
private:
    using iterator         = typename Derived::iterator;
    using const_iterator   = rubbish::const_iterator<iterator>;
    using reverse_iterator = rubbish::reverse_iterator<iterator>;

    using const_reverse_iterator = rubbish::const_iterator<reverse_iterator>;

    static       Derived& derived()       noexcept { return *static_cast<Derived*>(this); }
    static const Derived& derived() const noexcept { return *static_cast<const Derived*>(this); }
public:
    const_iterator cbegin() const { return const_iterator{derived().begin()}; }
    const_iterator cend()   const { return const_iterator{derived().end()}; }

    reverse_iterator rbegin() { return reverse_iterator{derived().end()}; }
    reverse_iterator rend()   { return reverse_iterator{derived().begin()}; }

    const_reverse_iterator crbegin() const { return const_iterator{rbegin()}; }
    const_reverse_iterator crend()   const { return const_iterator{rend}; }
};

} // namespace rubbish

#endif // RANGE_ACCESS
