#ifndef META_BITS_IS_ASSIGNABLE
#define META_BITS_IS_ASSIGNABLE

#include "meta/bits/constant.hpp"
#include "meta/bits/declval.hpp"
#include "meta/bits/void_t.hpp"

namespace stl {

template <class T, class U, class = void>
struct is_assignable : false_type {};

template <class T, class U>
struct is_assignable< T, U, void_t<decltype(declval<T>() = declval<U>())> > : true_type {};

} // namespace stl

#endif // META_BITS_IS_ASSIGNABLE
