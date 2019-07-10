#ifndef META_DECLVAL
#define META_DECLVAL

#include "meta/cvref/add_cvref.hpp"

namespace stl::meta {

template <class T>
constexpr add_rvalue_reference_t<T> declval() noexcept;

} // namespace stl::meta

#endif // META_DECLVAL
