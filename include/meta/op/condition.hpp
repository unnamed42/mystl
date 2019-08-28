#ifndef META_CONDITION
#define META_CONDITION

#include "meta/base/type.hpp"

namespace stl::meta {

template <bool B, class T, class F>
struct condition : type<T> {};

template <class T, class F>
struct condition<false, T, F> : type<F> {};

template <bool B, class T, class F>
using condition_t = typename condition<B, T, F>::type;

} // namespace stl::meta

#endif // META_CONDITION
