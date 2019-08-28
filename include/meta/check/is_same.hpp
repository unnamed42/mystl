#ifndef META_IS_SAME
#define META_IS_SAME

#include "meta/base/constant.hpp"

namespace stl::meta {

template <class T, class U> struct is_same       : false_type {};
template <class T>          struct is_same<T, T> : true_type  {};

} // namespace stl::meta

#endif // META_IS_SAME
