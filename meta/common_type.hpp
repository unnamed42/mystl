#ifndef META_COMMON_TYPE
#define META_COMMON_TYPE

#include "meta/decay.hpp"

#include "utility/declval.hpp"

namespace stl {

template <class ...Args> struct common_type;

template <class T>          struct common_type<T> : decay<T> {};
template <class T, class U> struct common_type<T> : decay<decltype(1 ? declval<T>() : declval<U>())> {};

template <class T, class U, class... V>
struct common_type<T, U, V...> {
    using type = typename common_type<
        typename common_type<T, U>::type,
        V...
    >::type;
};

template <class ...Args>
using common_type_t = typename common_type<Args...>::type;

} // namespace stl

#endif // META_COMMON_TYPE
