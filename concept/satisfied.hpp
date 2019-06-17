#ifndef CONCEPT_SATISFIED
#define CONCEPT_SATISFIED

#include "meta/logic.hpp"
#include "meta/enable_if.hpp"

namespace stl {

template <class ...Concepts>
using satisfied = typename enable_if<
    and_<Concepts...>::value
>::type;

} // namespace stl

#endif // CONCEPT_SATISFIED
