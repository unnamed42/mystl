#ifndef META_IS_CLASS
#define META_IS_CLASS

#include "meta/base/constant.hpp"
#include "meta/cvref/remove_cvref.hpp"

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

} // namespace stl

#endif // META_IS_CLASS
