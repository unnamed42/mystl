#ifndef META_BASE
#define META_BASE

namespace stl {

template <class T, T t>
struct constant { static constexpr auto value = t; };

using true_type  = constant<bool, true>;
using false_type = constant<bool, false>;

template <bool B>
using boolean = constant<bool, B>;

template <class T>
struct identity { using type = T; };

template <class T>
using identity_t = typename identity<T>::type;

} // namespace stl

#endif // META_BASE
