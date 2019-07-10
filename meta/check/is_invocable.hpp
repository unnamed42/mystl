#ifndef META_IS_INVOCABLE
#define META_IS_INVOCABLE

#include "func/invoke_result.hpp"

#include "meta/sfinae/is_detected.hpp"

namespace stl::meta {

template <class F, class ...Args>
struct is_invocable : is_detected<func::invoke_result_t, F, Args...>;

} // namespace stl::meta

#endif // META_IS_INVOCABLE
