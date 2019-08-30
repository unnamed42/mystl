#ifndef FUNCTIONAL_BITS_PARTIAL
#define FUNCTIONAL_BITS_PARTIAL

#include "meta/bits/remove_reference.hpp"
#include "meta/bits/is_invocable.hpp"

#include "utility/tuple.hpp"
#include "utility/bits/forward.hpp"
#include "utility/bits/forward_like.hpp"

#include "functional/bits/invoke.hpp"
#include "functional/bits/invoke_result.hpp"

#define STL_FWD(arg)       stl::forward<decltype(arg)>(arg)
#define STL_GET(arg)       stl::get<0>(STL_FWD(arg))
#define STL_FWD_CAP(arg)   stl::detail::fwd_capture(STL_FWD(arg))
#define STL_FWD_PACK(pack) stl::detail::fwd_capture_as_tuple(STL_FWD(pack)...)

namespace stl {

namespace detail {

    template <class Tuple>
    struct tuple_index
        : make_index_sequence<tuple_size_v<remove_reference_t<Tuple>>> {};

    template <class T>
    using tuple_index_t = typename tuple_index<T>::type;

    template <class F, class T1, class T2>
    constexpr decltype(auto) apply_capture2(F &&f, T1 &&t1, T2 &&t2) {
        return apply2([&xf=f](auto&& ...args) mutable -> decltype(auto) {
            return invoke(forward_like<F>(xf), STL_GET(args)...);
        }, forward<T1>(t1), forward<T2>(t2));
    }

    template <class T>
    constexpr auto fwd_capture(T &&t) {
        return tuple<T>(forward<T>(t));
    }

    template <class ...Ts>
    constexpr auto fwd_capture_as_tuple(Ts&& ...ts) {
        return make_tuple(fwd_capture(forward<Ts>(ts))...);
    }

} // namespace detail

template <class F>
constexpr decltype(auto) partial(F &&f) {
    if constexpr (is_invocable_v<F>)
        return forward<F>(f)();
    // we need to move xf, so xf cannot be const
    // without mutable xf is const qualified, which is not desired
    else return [xf = STL_FWD_CAP(f)] (auto&& ...p) mutable constexpr {
        return partial([
            // perfectly forwarding first argument pack into `pack`
            pack = STL_FWD_PACK(p), yf = move(xf)
        // mutable for same reason
        ] (auto&& ...xs) mutable constexpr
            // use explicit return type because decltype(auto) is SFINAE unfriendly
            -> invoke_result_t<F, decltype(p)..., decltype(xs)...> {
            return detail::apply_capture2([&yf](auto&& ...ys) constexpr
                -> invoke_result_t<F, decltype(ys)...> {
                return invoke(forward_like<F>(STL_GET(yf)), STL_FWD(ys)...);
            }, pack, STL_FWD_PACK(xs));
        });
    };
}

} // namespace stl

#undef STL_FWD_PACK
#undef STL_FWD_CAP
#undef STL_GET
#undef STL_FWD

#endif // FUNCTIONAL_BITS_PARTIAL
