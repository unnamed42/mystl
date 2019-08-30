#ifndef META_BITS_IS_CLASS
#define META_BITS_IS_CLASS

#include "meta/bits/constant.hpp"
#include "meta/bits/remove_cv.hpp"

namespace stl {

namespace detail {

    struct is_class_h {
        template <class T>
        static true_type  test(int T::*);

        static false_type test(...);
    };

    template <class T>
    struct is_class_impl : decltype(is_class_h::test(0)) {};

} // namespace detail

template <class T>
struct is_class : detail::is_class_impl<remove_cv_t<T>> {};
template <class T> constexpr inline bool is_class_v = is_class<T>::value;

} // namespace stl

#endif // META_BITS_IS_CLASS
