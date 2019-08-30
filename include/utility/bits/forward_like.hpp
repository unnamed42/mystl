#ifndef UTILITY_BITS_FORWARD_LIKE
#define UTILITY_BITS_FORWARD_LIKE

#include "meta/bits/condition.hpp"
#include "meta/bits/copy_ref.hpp"
#include "meta/bits/is_reference.hpp"
#include "meta/bits/add_reference.hpp"
#include "meta/bits/remove_reference.hpp"

namespace stl {

template <class T, class Source>
using forward_like_t = condition_t<!is_reference_v<Source>,
    add_rvalue_reference_t<remove_reference_t<T>>,
    copy_ref_t<T, Source>
>;

template <class TLike, class T>
inline constexpr forward_like_t<T, TLike> forward_like(T &&t) noexcept {
    static_assert(!(is_rvalue_reference_v<decltype(t)> &&
                    is_lvalue_reference_v<TLike>),
                  "forward-like: cannot forward rvalue like an lvalue");

    return static_cast<forward_like_t<T, TLike>>(t);
}

} // namespace stl

#endif // UTILITY_BITS_FORWARD_LIKE
