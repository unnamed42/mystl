#ifndef META_CONDITION
#define META_CONDITION

#include "meta/base.hpp"

namespace stl {

template <bool B, class T, class F>
struct condition { using type = T; };

template <class T, class F>
struct condition<false, T, F> { using type = F; };

template <bool B, class T, class F>
using condition_t = typename condition<B, T, F>::type;

} // namespace stl

#endif // META_CONDITION
