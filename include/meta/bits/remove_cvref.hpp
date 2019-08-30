#ifndef META_BITS_REMOVE_CVREF
#define META_BITS_REMOVE_CVREF

#include "meta/bits/remove_cv.hpp"
#include "meta/bits/remove_reference.hpp"

namespace stl {

template <class T>
struct remove_cvref : remove_cv<remove_reference_t<T>> {};

template <class T>
using remove_cvref_t = typename remove_cvref<T>::type;

} // namespace stl

#endif // META_BITS_REMOVE_CVREF
