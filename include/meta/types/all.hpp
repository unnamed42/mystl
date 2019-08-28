#ifndef META_ALL
#define META_ALL

#include "meta/base/constant.hpp"
#include "meta/op/logic.hpp"

namespace stl::meta {

template <template <class...> class Pred, class Types>
struct all : false_type {};

template <template <class...> class Pred, template <class...> class Types>
struct all<Pred, Types<>> : false_type {};

template <template <class...> class Pred, template <class...> class Types, class ...Ts>
struct all<Pred, Types<Ts...>> : and_<Pred<Ts>...> {};

} // namespace stl::meta

#endif // META_ALL
