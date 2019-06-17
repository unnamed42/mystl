#ifndef FUNCTIONAL_INVOKE
#define FUNCTIONAL_INVOKE

#include "meta/decay.hpp"
#include "meta/check.hpp"
#include "meta/is_member_pointer.hpp"

#include "utility/forward.hpp"

#include "functional/invoke_result.hpp"

namespace stl {

namespace detail {

    // Object is not required to be exactly Class
    template <class F, class Class, class Object, class ...Args>
    decltype(auto) invoke(F Class::* f, Object &&obj, Args&& ...args) {
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
    decltype(auto) invoke(F &&f, Args&& ...args) {
        return forward<F>(f)(forward<Args>(args)...);
    }

} // namespace detail

template <class F, class ...Args>
invoke_result_t<F, Args...> invoke(F &&f, Args&& ...args) {
    return detail::invoke(forward<F>(f), forward<Args>(args)...);
}

} // namespace stl

#endif // FUNCTIONAL_INVOKE
