#ifndef FUNCTIONAL_BITS_INVOKE
#define FUNCTIONAL_BITS_INVOKE

#include "meta/bits/decay.hpp"
#include "meta/bits/is_base_of.hpp"
#include "meta/bits/is_reference_wrapper.hpp"
#include "meta/bits/is_member_pointer.hpp"

#include "utility/bits/forward.hpp"

#include "functional/bits/invoke_result.hpp"

namespace stl {

namespace detail {

    // Object is not required to be exactly Class
    template <class F, class Class, class Object, class ...Args>
    constexpr decltype(auto) invoke_impl(F Class::* f, Object &&obj, Args&& ...args) {
        if constexpr (is_member_function_pointer_v<decltype(f)>) {
            if constexpr (is_base_of_v<F, decay_t<Object>>)
                return (forward<Object>(obj).*f)(forward<Args>(args)...);
            else if constexpr (is_reference_wrapper_v<decay_t<Object>>)
                return (obj.get().*f)(forward<Args>(args)...);
            else
                return ((*forward<Object>(obj)).*f)(forward<Args>(args)...);
        } else {
            static_assert(is_member_object_pointer_v<decltype(f)>);
            static_assert(sizeof...(args) == 0);
            if constexpr (is_base_of_v<F, decay_t<Object>>)
                return forward<Object>(obj).*f;
            else if constexpr (is_reference_wrapper_v<decay_t<Object>>)
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

} // namespace stl

#endif // FUNCTIONAL_BITS_INVOKE
