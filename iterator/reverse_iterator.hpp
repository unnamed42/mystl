#ifndef ITERATOR_REVERSE_ITERATOR
#define ITERATOR_REVERSE_ITERATOR

#include "iterator/iterator_traits.hpp"

namespace rubbish {

template <class Iterator>
class reverse_iterator {
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
public:
    reverse_iterator(const Iterator &iter) : m_iter(iter) {}
    reverse_iterator(const self_t &other) : m_iter(other.m_iter) {}

    Iterator base() const { return m_iter; }

    reference operator*()  const { return *(m_iter - 1); }
    pointer   operator->() const { return &operator*(); }

    self_t& operator++()    { --m_iter; return *this; }
    self_t  operator++(int) { auto i=*this; operator++(); return i; }
    self_t& operator--()    { ++m_iter; return *this; }
    self_t  operator--(int) { auto i=*this; operator--(); return i; }
    self_t& operator+=(difference_type diff)       { m_iter -= diff; return *this; }
    self_t  operator+ (difference_type diff) const { return self_t{m_iter - diff}; }
    self_t& operator-=(difference_type diff)       { m_iter += diff; return *this; }
    self_t  operator- (difference_type diff) const { return self_t{m_iter + diff}; }

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

} // namespace rubbish

#endif // ITERATOR_REVERSE_ITERATOR
