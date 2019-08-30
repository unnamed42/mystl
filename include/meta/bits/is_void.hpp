#ifndef META_BITS_IS_VOID
#define META_BITS_IS_VOID

#include "meta/bits/constant.hpp"
#include "meta/bits/is_same.hpp"
#include "meta/bits/remove_cv.hpp"

namespace stl {

template <class T> struct is_void : is_same<remove_cv_t<T>, void> {};
template <class T> constexpr inline bool is_void_v = is_void<T>::value;

} // namespace stl

#endif // META_BITS_IS_VOID
