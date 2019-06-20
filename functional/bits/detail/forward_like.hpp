#ifndef FUNCTIONAL_DETAIL_FORWARD_LIKE
#define FUNCTIONAL_DETAIL_FORWARD_LIKE

#include "meta/bits/condition.hpp"
#include "meta/bits/is_reference.hpp"
#include "meta/bits/add_reference.hpp"
#include "meta/bits/remove_reference.hpp"

namespace stl { namespace detail {

template <class T, class Source>
struct copy_referenceness_impl
    : condition<!is_reference_v<Source>,
          T,
          condition_t<is_lvalue_reference_v<Source>,
              add_lvalue_reference_t<T>,
              condition_t<is_rvalue_reference_v<Source>,
                add_rvalue_reference_t<T>,
                void
              >
          >
      > {};

template <class T, class Source>
struct copy_referenceness
    : copy_referenceness_impl<remove_reference_t<T>, Source> {};

template <class T, class Source>
using as_if_forwarded = condition_t<
    !is_reference_v<Source>,
    add_rvalue_reference_t<remove_reference_t<T>>,
    typename copy_referenceness<T, Source>::type
>;

template <class TLike, class T>
inline constexpr decltype(auto) forward_like(T &&t) noexcept {
    static_assert(!(is_rvalue_reference_v<decltype(t)> &&
                    is_lvalue_reference_v<TLike>),
    "forward-like: referenceness not satisfied");

    return static_cast<as_if_forwarded<T, TLike>>(t);
}

}} // namespace stl::detail

#endif // FUNCTIONAL_DETAIL_FORWARD_LIKE
