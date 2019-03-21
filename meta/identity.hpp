#ifndef META_IDENTITY
#define META_IDENTITY

namespace stl {

template <class T>
struct identity { using type = T; };

template <class T>
using identity_t = typename identity<T>::type;

} // namespace stl

#endif // META_IDENTITY
