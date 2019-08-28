#ifndef META_INSTANTIATION_OF
#define META_INSTANTIATION_OF

#include "meta/base/constant.hpp"

namespace stl::meta {

template <class, template <class...> class>
struct is_instantiation_of : false_type {};

template <template <class...> class Template, class ...Args>
struct is_instantiation_of<Template<Args...>, Template> : true_type {};

} } // namespace stl::meta

#endif // META_INSTANTIATION_OF
