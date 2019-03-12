#ifndef META_BASE
#define META_BASE

namespace rubbish {

template <class T, T t>
struct constant { static constexpr auto value = t; };

using true_type  = constant<bool, true>;
using false_type = constant<bool, false>;

template <class...> using void_t = void;

} // namespace rubbish

#endif // META_BASE
