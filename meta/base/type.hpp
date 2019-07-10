#ifndef META_TYPE
#define META_TYPE

namespace stl::meta {

namespace detail {

    template <class T>
    struct type_impl { using type = T; };

} // namespace detail

template <class T>
using type = detail::type_impl<T>;

} // namespace stl::meta

#endif // META_TYPE
