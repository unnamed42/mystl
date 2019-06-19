#ifndef META_BITS_REMOVE_CV
#define META_BITS_REMOVE_CV

#include "meta/bits/remove_const.hpp"
#include "meta/bits/remove_volatile.hpp"

namespace stl {

template <class T>
struct remove_cv : remove_volatile<remove_const_t<T>> {};

template <class T>
using remove_cv_t = typename remove_cv<T>::type;

} // namespace stl

#endif // META_BITS_REMOVE_CV
