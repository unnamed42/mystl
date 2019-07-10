#ifndef FUNCTIONAL_BITS_INVOKE_RESULT
#define FUNCTIONAL_BITS_INVOKE_RESULT

#include "meta/op/decay.hpp"
#include "meta/op/declval.hpp"
#include "meta/sfinae/enable_if.hpp"
#include "meta/check/is_base_of.hpp"
#include "meta/check/is_function.hpp"
#include "meta/check/is_reference_wrapper.hpp"

#include "utility/bits/forward.hpp"

namespace stl::func {

namespace detail {

    // normal functions
    template <class T>
    struct invoke_result_h {
        template <class F, class ...Args>
        static auto call(F &&f, Args&& ...args)
            -> decltype(forward<F>(f)(forward<Args>(args)...));
    };

    // member pointers(function pointer, member object pointer)
    template <class Class, class F>
    struct invoke_result_h<F Class::*> {
        template <class T, class Td = meta::decay_t<T>,
            class = meta::enable_if_t<meta::is_base_of<Class, Td>{}>
        >
        static auto get(T &&t) -> T&&;

        template <class T,
            class = meta::enable_if_t<meta::is_reference_wrapper<meta::decay_t<T>>{}>
        >
        static auto get(T &&t) -> decltype(t.get());

        template <class T, class Td = meta::decay_t<T>,
            class = meta::enable_if_t<!meta::is_base_of<Class, Td>{}>,
            class = meta::enable_if_t<!meta::is_reference_wrapper<Td>{}>
        >
        static auto get(T &&t) -> decltype(*forward<T>(t));

        template <class T, class ...Args, class F2,
            class = meta::enable_if_t<meta::is_function<F>{}>
        >
        static auto call(F2 Class::*pf, T &&t, Args&& ...args)
            -> decltype((invoke_result_h::get(forward<T>(t)).*pf)(forward<Args>(args)...));

        template <class T>
        static auto call(F Class::*pf, T &&t)
            -> decltype(invoke_result_h::get(forward<T>(t)).*pf);
    };

    template <class F, class ...Args, class Fd = meta::decay_t<F>>
    auto call_result(F &&f, Args&& ...args)
        -> decltype(invoke_result_h<Fd>::call(forward<F>(f), forward<Args>(args)...));

    template <class Void, class, class...>
    struct invoke_result_impl {};

    template <class F, class ...Args>
    struct invoke_result_impl<
        decltype(void(call_result(declval<F>(), declval<Args>()...))),
        F, Args...
    > {
        using type = decltype(call_result(declval<F>(), declval<Args>()...));
    };

} // namespace detail

template <class F, class ...Args>
struct invoke_result
    : detail::invoke_result_impl<void, F, Args...> {};

template <class F, class ...Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;

} // namespace stl::func

#endif // FUNCTIONAL_BITS_INVOKE_RESULT
