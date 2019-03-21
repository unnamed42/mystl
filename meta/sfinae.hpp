#ifndef META_SFINAE
#define META_SFINAE

#include "meta/condition.hpp"

namespace stl {

template <class...>
struct make_void { using type = void; };

template <class ...Args>
using void_t = typename make_void<Args...>::type;

template <bool B, class T = void>
struct enable_if {  };

template <class T>
struct enable_if<true, T> { using type = T; };

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <class ...Args>
using satisfied = typename enable_if<
    stl::and_<Args...>::value
>::type;

namespace detail {
    template <class, template <class...> class, class...>
    struct is_detected_impl : false_type {};

    template <template <class...> class Detector, class ...Args>
    struct is_detected_impl<void_t<Detector<Args...>>, Detector, Args...> : true_type {};
} // namespace detail

template <template <class...> class Detector, class ...Args>
struct is_detected : detail::is_detected_impl<void, Detector, Args...> {};

template <template <class...> class Detector, class ...Args>
constexpr inline bool is_detected_v = is_detected<Detector, Args...>::value;

} // namespace stl

#endif // META_SFINAE
