#ifndef CONCEPT_CALLABLE
#define CONCEPT_CALLABLE

#include "meta/cvref.hpp"
#include "meta/base.hpp"
#include "meta/bits/logic.hpp"
#include "meta/sfinae.hpp"
#include "meta/bits/is_function.hpp"

namespace stl {

namespace detail {

    template <class> struct is_member_pointer : false_type {};

    template <class Class, class T>
    struct is_member_pointer<T(Class*)> : true_type {};

    template <class Class, class Ret, class ...Args>
    struct is_member_pointer<Ret(Class::*)(Args...)> : true_type {};

    // TODO: find template-d operator(), eg. std::less<void>
    template <class T>
    using operator_check = decltype(&T::operator());
} // namespace detail

template <class T>
struct callable : or_<
    is_function<remove_pointer_t<T>>,
    is_function<remove_reference_t<T>>,
    is_detected<detail::operator_check, T>
> {};

} // namespace stl

#endif // CONCEPT_CALLABLE
