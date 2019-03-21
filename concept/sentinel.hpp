#ifndef CONCEPT_SENTINEL
#define CONCEPT_SENTINEL

#include "meta/condition.hpp"
#include "concept/comparable.hpp"

namespace stl {

template <class Sentinel, class Input>
struct sentinel : stl::and_<
    stl::equality_comparable<Sentinel, Input>,
    stl::inequality_comparable<Sentinel, Input>
> {};

} // namespace stl

#endif // CONCEPT_SENTINEL
