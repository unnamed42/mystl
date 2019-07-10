#ifndef META_VALUES
#define META_VALUES

namespace stl::meta {

template <class T, T...>
struct values { using type = values; };

} // namespace stl::meta

#endif // META_VALUES
