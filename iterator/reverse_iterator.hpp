#ifndef ITERATOR_REVERSE_ITERATOR
#define ITERATOR_REVERSE_ITERATOR

#include "iterator/iterator_traits.hpp"

#include "crtp/iterator_facade.hpp"

namespace stl {

template <class Iterator>
class reverse_iterator : iterator_facade<reverse_iterator<Iterator>,
                                         typename iterator_traits<Iterator>::value_type,
                                         typename iterator_traits<Iterator>::reference,
                                         typename iterator_traits<Iterator>::pointer,
                                         typename iterator_traits<Iterator>::difference_type> {
    friend class iterator_core_access;
private:
    using traits_t = iterator_traits<Iterator>;
    using self_t   = reverse_iterator<Iterator>;
public:
    using value_type        = typename traits_t::value_type;
    using pointer           = typename traits_t::pointer;
    using reference         = typename traits_t::reference;
    using difference_type   = typename traits_t::difference_type;
    using iterator_category = typename traits_t::iterator_category;
private:
    Iterator m_iter;
private:
    void increment() { --m_iter; }
    void decrement() { ++m_iter; }
    void advance(difference_type diff) { m_iter -= diff; }
    reference deref() { return *(m_iter - 1); }
public:
    reverse_iterator(const Iterator &iter) : m_iter(iter) {}
    reverse_iterator(const self_t &other) : m_iter(other.m_iter) {}

    Iterator base() const { return m_iter; }

    self_t& operator=(const Iterator &iter) { m_iter = iter; return *this; }
    self_t& operator=(const self_t &other)  { m_iter = other.m_iter; return *this; }
};

template <class IterL, class IterR>
inline bool operator<(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs) { return lhs.base() < rhs.base(); }
template <class IterL, class IterR>
inline bool operator>(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs) { return rhs < lhs; }
template <class IterL, class IterR>
inline bool operator<=(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs) { return !(lhs > rhs); }
template <class IterL, class IterR>
inline bool operator>=(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs) { return !(lhs < rhs); }
template <class IterL, class IterR>
inline bool operator==(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs) { return lhs.base() == rhs.base(); }
template <class IterL, class IterR>
inline bool operator!=(const reverse_iterator<IterL> &lhs, const reverse_iterator<IterR> &rhs) { return !(lhs == rhs); }

} // namespace stl

#endif // ITERATOR_REVERSE_ITERATOR
