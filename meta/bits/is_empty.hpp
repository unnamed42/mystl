#ifndef META_BITS_IS_EMPTY
#define META_BITS_IS_EMPTY

#include "meta/bits/constant.hpp"

namespace stl {

namespace detail {

    template <bool, class T>
    struct is_empty_h : T { unsigned long long data; };

    template <class T>
    struct is_empty_h<false, T> { unsigned long long data; };

} // namespace detail

template <class T>
struct is_empty
    : boolean<(sizeof(detail::is_empty_h<is_class_v<T>, T>) == sizeof(unsigned long long))> {};

template <class T>
constexpr inline bool is_empty_v = is_empty<T>::value;

} // namespace stl

#endif // META_BITS_IS_EMPTY
