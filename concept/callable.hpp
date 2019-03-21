#ifndef CONCEPT_CALLABLE
#define CONCEPT_CALLABLE

#include "meta/ref.hpp"
#include "meta/sfinae.hpp"
#include "meta/condition.hpp"
#include "concept/function.hpp"

namespace stl {

namespace detail {
    // TODO: find template-d operator(), eg. std::less<void>
    template <class T>
    using operator_check = decltype(&T::operator());
} // namespace detail

template <class T>
struct callable : stl::or_<
    stl::function<stl::remove_pointer_t<T>>,
    stl::function<stl::remove_reference_t<T>>,
    stl::is_detected<detail::operator_check, T>
> {};

} // namespace stl

#endif // CONCEPT_CALLABLE
