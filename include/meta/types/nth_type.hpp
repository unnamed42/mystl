#ifndef META_NTH_TYPE
#define META_NTH_TYPE

#include "def.hpp"

#include "meta/base/type.hpp"

namespace stl::meta {

template <class Types, size_t Idx> struct nth_type {};

template <size_t Idx, template <class...> class Types, class T, class Ts...>
struct nth_type<Types<T, Ts...>, Idx> : nth_type<Types<Ts...>, Idx - 1> {};

template <template <class...> class Types, class T, class Ts...>
struct nth_type<Types<T, Ts...>, 0> : type<T> {};

template <size_t Idx, template <class...> class Types>
struct nth_type<Types<>, Idx> {};

} // namespace stl::meta

#endif // META_NTH_TYPE
