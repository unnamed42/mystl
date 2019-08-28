#ifndef META_VOID_T
#define META_VOID_T

#include "meta/base/type.hpp"

namespace stl::meta {

template <class...>
struct void_type : type<void> {};

template <class ...Args>
using void_t = typename void_type<Args...>::type;

} // namespace stl::meta

#endif // META_VOID_T
