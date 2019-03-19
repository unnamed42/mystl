#ifndef META_DETECT
#define META_DETECT

#include "meta/void_t.hpp"

namespace rubbish {

namespace detail {
    template <class, template <class...> class, class...>
    struct is_detected_impl : false_type {};

    template <template <class...> class Detector, class ...Args>
    struct is_detected_impl<void_t<Detector<Args...>>, Detector, Args...> : true_type {};
} // namespace detail

template <template <class...> class Detector, class ...Args>
struct is_detected : detail::is_detected_impl<void, Detector, Args...> {};

template <template <class...> class Detector, class ...Args>
constexpr inline bool is_detected_v = is_detected<T, Detector>::value;

} // namespace rubbish

#endif // META_DETECT
