#ifndef META_BITS_VOID_T
#define META_BITS_VOID_T

#include "meta/bits/identity.hpp"

namespace stl {

template <class...>
struct void_type : identity<void> {};

template <class ...Args>
using void_t = typename void_type<Args...>::type;

} // namespace stl

#endif // META_BITS_VOID_T
