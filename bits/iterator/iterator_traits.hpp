#ifndef ITERATOR_ITERATOR_TRAITS
#define ITERATOR_ITERATOR_TRAITS

#include "def.hpp"

namespace rubbish {

struct random_access_iterator_tag {};
struct bidirectional_iterator_tag {};
struct forward_iterator_tag {};

template <class Iterator>
struct iterator_traits {
    using value_type        = typename Iterator::value_type;
    using pointer           = typename Iterator::pointer;
    using reference         = typename Iterator::reference;
    using difference_type   = typename Iterator::difference_type;
    using iterator_category = typename Iterator::iterator_category;
};

template <class T>
struct iterator_traits<T*> {
    using value_type        = T;
    using pointer           = T*;
    using reference         = T&;
    using difference_type   = ptrdiff_t;
    using iterator_category = random_access_iterator_tag;
};

template <class T>
struct iterator_traits<const T*> {
    using value_type        = T;
    using pointer           = const T*;
    using reference         = const T&;
    using difference_type   = ptrdiff_t;
    using iterator_category = random_access_iterator_tag;
};

} // namespace rubbish

#endif // ITERATOR_ITERATOR_TRAITS
