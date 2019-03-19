#ifndef CRTP_RANGE_ACCESS
#define CRTP_RANGE_ACCESS

#include "iterator/const_iterator.hpp"
#include "iterator/reverse_iterator.hpp"

namespace rubbish {

template <class Derived, class Iterator>
class range_access {
private:
    using const_iterator   = rubbish::const_iterator<Iterator>;
    using reverse_iterator = rubbish::reverse_iterator<Iterator>;
    using const_reverse_iterator = rubbish::const_iterator<reverse_iterator>;

          Derived& derived()       noexcept { return *static_cast<Derived*>(this); }
    const Derived& derived() const noexcept { return *static_cast<const Derived*>(this); }
public:
    const_iterator cbegin() const { return const_iterator{derived().begin()}; }
    const_iterator cend()   const { return const_iterator{derived().end()}; }

    reverse_iterator rbegin() { return reverse_iterator{derived().end()}; }
    reverse_iterator rend()   { return reverse_iterator{derived().begin()}; }

    const_reverse_iterator crbegin() const { return const_iterator{rbegin()}; }
    const_reverse_iterator crend()   const { return const_iterator{rend}; }
};

} // namespace rubbish

#endif // CRTP_RANGE_ACCESS
