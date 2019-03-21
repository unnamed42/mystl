#ifndef CONCEPT_SATISFIED
#define CONCEPT_SATISFIED

#include "meta/condition.hpp"
#include "meta/enable_if.hpp"

namespace stl {

template <class ...Concepts>
using satisfied = typename stl::enable_if<
    stl::and_<Concepts...>::value
>::type;

} // namespace stl

#endif // CONCEPT_SATISFIED
