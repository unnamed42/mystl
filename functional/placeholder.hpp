#ifndef FUNCTIONAL_PLACEHOLDER
#define FUNCTIONAL_PLACEHOLDER

#include "utility/forward.hpp"

namespace stl {

template <int I>
struct placeholder {};

namespace detail {



} // namespace detail

static constexpr inline placeholder<0> _{};

} // namespace stl

#endif // FUNCTIONAL_PLACEHOLDER
