#ifndef ITERATOR_CONST_ITERATOR
#define ITERATOR_CONST_ITERATOR

#include "meta/bits/remove_pointer.hpp"
#include "meta/bits/remove_reference.hpp"

#include "iterator/iterator_traits.hpp"

#include "crtp/comparable.hpp"
#include "crtp/iterator_facade.hpp"

#include "utility/bits/compare.hpp"

namespace stl {

template <class Iterator>
class const_iterator : iterator_facade<const_iterator<Iterator>,
                                       typename iterator_traits<Iterator>::value_type,
                                       typename iterator_traits<Iterator>::reference,
                                       typename iterator_traits<Iterator>::pointer,
                                       typename iterator_traits<Iterator>::difference_type>,
                       comparable<const_iterator<Iterator>, Iterator> {
    friend class iterator_core_access;
    friend class comparable_access;
private:
    using traits_t = iterator_traits<Iterator>;
    using self_t   = const_iterator<Iterator>;
public:
    using value_type        = typename traits_t::value_type;
    using pointer           = const remove_pointer_t<typename traits_t::pointer>*;
    using reference         = const remove_reference_t<typename traits_t::reference>&;
    using difference_type   = typename traits_t::difference_type;
    using iterator_category = typename traits_t::iterator_category;
private:
    Iterator m_cursor;
private:
    void increment() { ++m_cursor; }
    void decrement() { --m_cursor; }
    void advance(difference_type diff) { m_cursor += diff; }
    reference deref() { return *m_cursor; }
    int compare(const Iterator &i) const { return stl::compare(*this, i); }
public:
    const_iterator(Iterator iter) : m_cursor(iter) {}
    const_iterator(const self_t &other) : m_cursor(other.m_cursor) {}

    Iterator  base()       const { return m_cursor; }

    self_t& operator=(Iterator iter)       { m_cursor = iter; return *this; }
    self_t& operator=(const self_t &other) { m_cursor = other.m_cursor; return *this; }
};

template <class IterL, class IterR>
inline bool operator<(const const_iterator<IterL> &lhs, const const_iterator<IterR> &rhs) { return lhs.base() < rhs.base(); }
template <class IterL, class IterR>
inline bool operator>(const const_iterator<IterL> &lhs, const const_iterator<IterR> &rhs) { return rhs < lhs; }
template <class IterL, class IterR>
inline bool operator<=(const const_iterator<IterL> &lhs, const const_iterator<IterR> &rhs) { return !(lhs > rhs); }
template <class IterL, class IterR>
inline bool operator>=(const const_iterator<IterL> &lhs, const const_iterator<IterR> &rhs) { return !(lhs < rhs); }
template <class IterL, class IterR>
inline bool operator==(const const_iterator<IterL> &lhs, const const_iterator<IterR> &rhs) { return lhs.base() == rhs.base(); }
template <class IterL, class IterR>
inline bool operator!=(const const_iterator<IterL> &lhs, const const_iterator<IterR> &rhs) { return !(lhs == rhs); }

} // namespace stl

#endif // ITERATOR_CONST_ITERATOR
