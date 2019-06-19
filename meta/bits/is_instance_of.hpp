#ifndef META_BITS_IS_INSTANCE_OF
#define META_BITS_IS_INSTANCE_OF

#include "meta/bits/constant.hpp"

namespace stl {

template <class T, template <class...> class Template>
struct is_instance_of : false_type {};

template <template <class...> class Template, class ...Args>
struct is_instance_of<Template<Args...>, Template> : true_type {};

template <class T, template <class...> class Template>
constexpr inline bool is_instance_of_v = is_instance_of<T, Template>::value;

} // namespace stl

#endif // META_BITS_IS_INSTANCE_OF
