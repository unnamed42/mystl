#ifndef UTILITY_BITS_IDENTITY
#define UTILITY_BITS_IDENTITY

namespace stl {

template <class T>
struct identity { using type = T; };

template <class T>
using identity_t = typename identity<T>::type;

} // namespace stl

#endif // UTILITY_BITS_IDENTITY
