#ifndef META_BITS_DECLVAL
#define META_BITS_DECLVAL

#include "meta/bits/add_reference.hpp"

namespace stl {

template <class T>
constexpr add_rvalue_reference_t<T> declval() noexcept;

} // namespace stl

#endif // META_BITS_DECLVAL
