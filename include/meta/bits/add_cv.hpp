#ifndef META_BITS_ADD_CV
#define META_BITS_ADD_CV

#include "meta/bits/add_const.hpp"
#include "meta/bits/add_volatile.hpp"

namespace stl {

template <class T>
struct add_cv : add_volatile<add_const_t<T>> {};

template <class T>
using add_cv_t = typename add_cv<T>::type;

} // namespace stl

#endif // META_BITS_ADD_CV
