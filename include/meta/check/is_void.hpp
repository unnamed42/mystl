#ifndef META_IS_VOID
#define META_IS_VOID

#include "meta/base/constant.hpp"

namespace stl::meta {

template <class T> struct is_void : false_type {};
template <> struct is_void<void>                : true_type {};
template <> struct is_void<const void>          : true_type {};
template <> struct is_void<volatile void>       : true_type {};
template <> struct is_void<const volatile void> : true_type {};

} // namespace stl::meta

#endif // META_IS_VOID
