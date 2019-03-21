#ifndef CRTP_ITERATOR_FACADE
#define CRTP_ITERATOR_FACADE

#include "def.hpp"

namespace stl {

class iterator_core_access {
    template <class D, class V, class R, class P, class Diff> friend class iterator_facade;

    template <class T>
    static void increment(T &t) { t.increment(); }

    template <class T>
    static void decrement(T &t) { t.decrement(); }

    template <class T>
    static decltype(auto) deref(T &t) { return t.deref(); }

    template <class T, class D>
    static void advance(T &t, D diff) { t.advance(diff); }
};

template <class Derived, class V, class R = V&, class P = V*, class D = ptrdiff_t>
class iterator_facade {
private:
          Derived& derived()       noexcept { return *static_cast<Derived*>(this); }
    const Derived& derived() const noexcept { return *static_cast<const Derived*>(this); }
public:
    using value_type      = V;
    using reference       = R;
    using pointer         = P;
    using difference_type = D;
private:
    using access = stl::iterator_core_access;
public:
    reference operator*()  { return access::deref(derived()); }
    pointer   operator->() { return &operator*(); }

    Derived& operator++()    { access::increment(derived()); return derived(); }
    Derived  operator++(int) { auto copy = derived(); access::increment(derived()); return copy; }
    Derived& operator--()    { access::decrement(derived()); return derived(); }
    Derived  operator--(int) { auto copy = derived(); access::decrement(derived()); return copy; }

    Derived& operator+=(difference_type diff)       { access::advance(derived(), diff); return *this; }
    Derived  operator+ (difference_type diff) const { auto copy = derived(); access::advance(copy, diff); return copy; }
    Derived& operator-=(difference_type diff)       { access::advance(derived(), -diff); return *this; }
    Derived  operator- (difference_type diff) const { auto copy = derived(); access::advance(copy, -diff); return copy; }
};

} // namespace stl

#endif // CRTP_ITERATOR_FACADE
