#ifndef UTILITY_DECLVAL
#define UTILITY_DECLVAL

#include "meta/ref.hpp"

namespace stl {

template <class T>
constexpr add_rvalue_reference_t<T> declval() noexcept;

} // namespace stl

#endif // UTILITY_DECLVAL
