#ifndef META_COMMON_TYPE
#define META_COMMON_TYPE

#include "meta/op/decay.hpp"
#include "meta/op/declval.hpp"

namespace stl::meta {

template <class ...Args> struct common_type;

template <class T>          struct common_type<T> : decay<T> {};
template <class T, class U> struct common_type<T> : decay<decltype(1 ? declval<T>() : declval<U>())> {};

template <class T, class U, class... V>
struct common_type<T, U, V...>
    : common_type<typename common_type<T, U>::type, V...> {};

template <class ...Args>
using common_type_t = typename common_type<Args...>::type;

} // namespace stl::meta

#endif // META_COMMON_TYPE
