#ifndef ITERATOR_CONST_ITERATOR
#define ITERATOR_CONST_ITERATOR

#include "meta/cv.hpp"
#include "meta/ref.hpp"
#include "iterator/iterator_traits.hpp"

namespace stl {

template <class Iterator>
class const_iterator {
private:
    using traits_t = stl::iterator_traits<Iterator>;
    using self_t   = stl::const_iterator<Iterator>;
public:
    using value_type        = typename traits_t::value_type;
    using pointer           = const remove_pointer_t<typename traits_t::pointer>*;
    using reference         = const remove_reference_t<typename traits_t::reference>&;
    using difference_type   = typename traits_t::difference_type;
    using iterator_category = typename traits_t::iterator_category;
private:
    Iterator m_cursor;
public:
    const_iterator(Iterator iter) : m_cursor(iter) {}
    const_iterator(const self_t &other) : m_cursor(other.m_cursor) {}

    reference operator*()  const { return static_cast<reference>(*m_cursor); }
    pointer   operator->() const { return &operator*(); }
    Iterator  base()       const { return m_cursor; }

    self_t& operator++()    { ++m_cursor; return *this; }
    self_t  operator++(int) { auto i=*this; operator++(); return i;}
    self_t& operator--()    { --m_cursor; return *this; }
    self_t  operator--(int) { auto i=*this; operator--(); return i;}

    self_t& operator+=(difference_type diff)       { m_cursor+=diff; return *this; }
    self_t  operator+ (difference_type diff) const { return self_t{m_cursor + diff}; }
    self_t& operator-=(difference_type diff)       { m_cursor -= diff; return *this; }
    self_t  operator- (difference_type diff) const { return self_t{m_cursor - diff}; }

    self_t& operator=(Iterator iter)       { m_cursor = iter; return *this; }
    self_t& operator=(const self_t &other) { m_cursor = other.m_cursor; return *this; }
};

template <class IterL, class IterR>
inline bool operator<(const stl::const_iterator<IterL> &lhs, const stl::const_iterator<IterR> &rhs) { return lhs.base() < rhs.base(); }
template <class IterL, class IterR>
inline bool operator>(const stl::const_iterator<IterL> &lhs, const stl::const_iterator<IterR> &rhs) { return rhs < lhs; }
template <class IterL, class IterR>
inline bool operator<=(const stl::const_iterator<IterL> &lhs, const stl::const_iterator<IterR> &rhs) { return !(lhs > rhs); }
template <class IterL, class IterR>
inline bool operator>=(const stl::const_iterator<IterL> &lhs, const stl::const_iterator<IterR> &rhs) { return !(lhs < rhs); }
template <class IterL, class IterR>
inline bool operator==(const stl::const_iterator<IterL> &lhs, const stl::const_iterator<IterR> &rhs) { return lhs.base() == rhs.base(); }
template <class IterL, class IterR>
inline bool operator!=(const stl::const_iterator<IterL> &lhs, const stl::const_iterator<IterR> &rhs) { return !(lhs == rhs); }

// Make stl::const_iterator and underlying iterator co-operable
template <class Iter> inline bool operator<(const Iter &lhs, const stl::const_iterator<Iter> &rhs) { return lhs < rhs.base(); }
template <class Iter> inline bool operator>(const Iter &lhs, const stl::const_iterator<Iter> &rhs) { return lhs > rhs.base(); }
template <class Iter> inline bool operator<=(const Iter &lhs, const stl::const_iterator<Iter> &rhs) { return !(lhs > rhs); }
template <class Iter> inline bool operator>=(const Iter &lhs, const stl::const_iterator<Iter> &rhs) { return !(lhs < rhs); }
template <class Iter> inline bool operator==(const Iter &lhs, const stl::const_iterator<Iter> &rhs) { return lhs == rhs.base(); }
template <class Iter> inline bool operator!=(const Iter &lhs, const stl::const_iterator<Iter> &rhs) { return !(lhs == rhs); }
template <class Iter> inline bool operator<(const stl::const_iterator<Iter> &lhs, const Iter &rhs) { return rhs > lhs; }
template <class Iter> inline bool operator>(const stl::const_iterator<Iter> &lhs, const Iter &rhs) { return rhs < lhs; }
template <class Iter> inline bool operator<=(const stl::const_iterator<Iter> &lhs, const Iter &rhs) { return rhs >= lhs; }
template <class Iter> inline bool operator>=(const stl::const_iterator<Iter> &lhs, const Iter &rhs) { return rhs <= lhs; }
template <class Iter> inline bool operator==(const stl::const_iterator<Iter> &lhs, const Iter &rhs) { return rhs == lhs; }
template <class Iter> inline bool operator!=(const stl::const_iterator<Iter> &lhs, const Iter &rhs) { return rhs != lhs; }

} // namespace stl

#endif // ITERATOR_CONST_ITERATOR
