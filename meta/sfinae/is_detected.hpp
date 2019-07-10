#ifndef META_IS_DETECTED
#define META_IS_DETECTED

#include "meta/base/constant.hpp"
#include "meta/sfinae/void_t.hpp"

namespace stl::meta {

namespace detail {
    template <class, template <class...> class, class...>
    struct is_detected_impl : false_type {};

    template <template <class...> class Detector, class ...Args>
    struct is_detected_impl<void_t<Detector<Args...>>, Detector, Args...> : true_type {};
} // namespace detail

template <template <class...> class Detector, class ...Args>
struct is_detected : detail::is_detected_impl<void, Detector, Args...> {};

} // namespace stl::meta

#endif // META_IS_DETECTED
