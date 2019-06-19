#ifndef META_BITS_CONSTANT
#define META_BITS_CONSTANT

namespace stl {

template <class T, T t>
struct constant { static constexpr auto value = t; };

using true_type  = constant<bool, true>;
using false_type = constant<bool, false>;

template <bool B>
using boolean = constant<bool, B>;

} // namespace stl

#endif // META_BITS_CONSTANT
