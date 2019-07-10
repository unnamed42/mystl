#ifndef META_TYPES
#define META_TYPES

namespace stl::meta {

template <class...>
struct types { using type = types; };

} // namespace stl::meta

#endif // META_TYPES
