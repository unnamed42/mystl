#ifndef META_BITS_IS_BASE_OF
#define META_BITS_IS_BASE_OF

#include "meta/bits/constant.hpp"
#include "meta/bits/remove_cv.hpp"

namespace stl {

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
    struct is_base_of
        : decltype(is_base_of_h<B, D>::test(is_base_of_h<B, D>{}, int{})) {};

} // namespace detail

template <class Base, class Derived>
struct is_base_of : detail::is_base_of<remove_cv_t<Base>, remove_cv_t<Derived>> {};
template <class B, class D> constexpr inline bool is_base_of_v = is_base_of<B, D>::value;

} // namespace stl

#endif // META_BITS_IS_BASE_OF
