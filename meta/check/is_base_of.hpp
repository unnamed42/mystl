#ifndef META_IS_BASE_OF
#define META_IS_BASE_OF

#include "meta/base/constant.hpp"
#include "meta/cvref/remove_cvref.hpp"

namespace stl::meta {

namespace detail {

    // from https://stackoverflow.com/a/2913870
    template <class B, class D>
    struct is_base_of_h {
        operator B*() const;
        operator D*();

        template <class T>
        static true_type  test(D*, T);

        static false_type test(B*, int);
    };

    template <class B, class D>
    struct is_base_of_impl
        : decltype(is_base_of_h<B, D>::test(is_base_of_h<B, D>{}, int{})) {};

} // namespace detail

template <class Base, class Derived>
struct is_base_of : detail::is_base_of_impl<remove_cv_t<Base>, remove_cv_t<Derived>> {};

} // namespace stl::meta

#endif // META_IS_BASE_OF
