#ifndef FUNCTIONAL_INVOKE_RESULT
#define FUNCTIONAL_INVOKE_RESULT

#include "meta/check.hpp"
#include "meta/decay.hpp"
#include "meta/sfinae.hpp"
#include "meta/is_function.hpp"

#include "utility/forward.hpp"
#include "utility/declval.hpp"

namespace stl {

namespace detail {

    // normal functions
    template <class T>
    struct invoke_impl {
        template <class F, class ...Args>
        static auto call(F &&f, Args&& ...args)
            -> decltype(forward<F>(f)(forward<Args>(args)...));
    };

    // member pointers(function pointer, member object pointer)
    template <class Class, class F>
    struct invoke_impl<F Class::*> {
        template <class T, class Td = decay_t<T>,
            class = enable_if_t<is_base_of_v<Class, Td>>
        >
        static auto get(T &&t) -> T&&;

        template <class T, class Td = decay_t<T>,
            class = enable_if_t<is_reference_wrapper_v<Td>>
        >
        static auto get(T &&t) -> decltype(t.get());

        template <class T, class Td = decay_t<T>,
            class = enable_if_t<!is_base_of_v<Class, Td>>,
            class = enable_if_t<!is_reference_wrapper_v<Td>>
        >
        static auto get(T &&t) -> decltype(*forward<T>(t));

        template <class T, class ...Args, class F2,
            class = enable_if_t<is_function_v<F>>
        >
        static auto call(F2 Class::*pf, T &&t, Args&& ...args)
            -> decltype((invoke_impl::get(forward<T>(t)).*pf)(forward<Args>(args)...));

        template <class T>
        static auto call(F Class::*pf, T &&t)
            -> decltype(invoke_impl::get(forward<T>(t)).*pf);
    };

    template <class F, class ...Args, class Fd = decay_t<F>>
    auto call_result(F &&f, Args&& ...args)
        -> decltype(invoke_impl<Fd>::call(forward<F>(f), forward<Args>(args)...));

    template <class Void, class, class...>
    struct invoke_result {};

    template <class F, class ...Args>
    struct invoke_result<
        decltype(void(call_result(declval<F>(), declval<Args>()...))),
        F, Args...
    > {
        using type = decltype(call_result(declval<F>(), declval<Args>()...));
    };

} // namespace detail

template <class F, class ...Args>
struct invoke_result
    : detail::invoke_result<void, F, Args...> {};

template <class F, class ...Args>
using invoke_result_t = typename invoke_result<F, Args...>::type;

} // namespace stl

#endif // FUNCTIONAL_INVOKE_RESULT
