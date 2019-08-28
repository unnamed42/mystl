#ifndef META_SATISFIED
#define META_SATISFIED

#include "meta/base/type.hpp"
#include "meta/sfinae/void_t.hpp"

namespace stl::meta {

namespace detail {

    template <bool> struct satisfied_impl {};
    template <> struct satisfied_impl<true> : type<void> {};

} // namespace detail

// convert boolean meta checkers to SFINAE helpers
// a more elegant way than enable_if
template <template <class...> class Pred, class ...Args>
using satisfied = void_t<typename detail::satisfied_impl<Pred<Args...>::value>::type>;

} // namespace stl::meta

#endif // META_SATISFIED
