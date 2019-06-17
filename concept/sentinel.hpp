#ifndef CONCEPT_SENTINEL
#define CONCEPT_SENTINEL

#include "meta/logic.hpp"
#include "concept/comparable.hpp"

namespace stl {

template <class Sentinel, class Input>
struct sentinel : and_<
    equality_comparable<Sentinel, Input>,
    inequality_comparable<Sentinel, Input>
> {};

} // namespace stl

#endif // CONCEPT_SENTINEL
