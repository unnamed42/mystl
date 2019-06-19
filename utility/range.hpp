#ifndef UTILITY_RANGE
#define UTILITY_RANGE

#include "meta/bits/remove_reference.hpp"

#include "utility/bits/forward.hpp"

#include "crtp/comparable.hpp"
#include "crtp/iterator_facade.hpp"

namespace stl {

namespace detail {
    struct range_sentinel {};
} // namespace detail

template <class T>
class range_iterator : public iterator_facade<range_iterator<T>, T>,
                              comparable<range_iterator<T>, range_iterator<T>> {
    friend class comparable_access;
    friend class iterator_core_access;
private:
    T val, last;
private:
    using self = range_iterator<T>;
protected:
    int compare(const detail::range_sentinel&) const { return val != last; }
    int compare(const self &o) const { return val - o.val; }
    void increment() { ++val; }
    void decrement() { --val; }
    T&   deref() { return val; }
public:
    range_iterator(const T &v, const T &l)
        : val(v), last(l) {}

    range_iterator(const self &o)
        : range_iterator(o.val, o.last) {}

    self                   begin() { return *this; }
    detail::range_sentinel end()   { return {}; }

    bool operator==(detail::range_sentinel) const { return val == last; }
    bool operator!=(detail::range_sentinel) const { return !operator==({}); }
};

template <class T>
range_iterator<remove_reference_t<T>> range(T &&first, T &&last) {
    return { forward<T>(first), forward<T>(last) };
}

} // namespace stl

#endif // UTILITY_RANGE
