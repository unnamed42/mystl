#ifndef FUNCTIONAL_INVOKE
#define FUNCTIONAL_INVOKE

#include "meta/op/decay.hpp"
#include "meta/check/is_base_of.hpp"
#include "meta/check/is_reference_wrapper.hpp"
#include "meta/check/is_member_pointer.hpp"

#include "utility/bits/forward.hpp"

#include "func/invoke_result.hpp"

namespace stl::func {

namespace detail {

    // Object is not required to be exactly Class
    template <class F, class Class, class Object, class ...Args>
    constexpr decltype(auto) invoke_impl(F Class::* f, Object &&obj, Args&& ...args) {
        if constexpr (meta::is_member_function_pointer<decltype(f)>{}) {
            if constexpr (meta::is_base_of<Class, meta::decay_t<Object>>{})
                return (forward<Object>(obj).*f)(forward<Args>(args)...);
            else if constexpr (meta::is_reference_wrapper<meta::decay_t<Object>>{})
                return (obj.get().*f)(forward<Args>(args)...);
            else
                return ((*forward<Object>(obj)).*f)(forward<Args>(args)...);
        } else {
            static_assert(meta::is_member_object_pointer<decltype(f)>{});
            static_assert(sizeof...(args) == 0);
            if constexpr (meta::is_base_of<Class, meta::decay_t<Object>>{})
                return forward<Object>(obj).*f;
            else if constexpr (meta::is_reference_wrapper<meta::decay_t<Object>>{})
                return obj.get().*f;
            else
                return (*forward<Object>(obj)).*f;
        }
    }

    template <class F, class ...Args>
    constexpr decltype(auto) invoke_impl(F &&f, Args&& ...args) {
        return forward<F>(f)(forward<Args>(args)...);
    }

} // namespace detail

template <class F, class ...Args>
constexpr invoke_result_t<F, Args...> invoke(F &&f, Args&& ...args) {
    return detail::invoke_impl(forward<F>(f), forward<Args>(args)...);
}

} // namespace stl::func

#endif // FUNCTIONAL_INVOKE
