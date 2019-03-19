#ifndef CRTP_COMMON_TYPE
#define CRTP_COMMON_TYPE

#include "meta/decay.hpp"
#include "utility/forward.hpp"

namespace rubbish {

template <class ...Args> struct common_type {};

template <class T> struct common_type<T> { using type = decay_t<T>; };

template <class T> struct common_type<T> {
    using type = decay_t<decltype(1 ? declval<T>() : declval<U>())>;
};

template <class T, class U, class... V> struct common_type<T, U, V...> {
    using type = typename common_type<
        typename common_type<T, U>::type,
        V...
    >::type;
};

template <class ...Args>
using common_type_t = typename common_type<Args...>::type;

} // namespace rubbish

#endif // CRTP_COMMON_TYPE
