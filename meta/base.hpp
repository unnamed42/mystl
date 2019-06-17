#ifndef META_BASE
#define META_BASE

namespace stl {

template <class T, T t>
struct constant { static constexpr auto value = t; };

using true_type  = constant<bool, true>;
using false_type = constant<bool, false>;

namespace detail {
    struct yes_t { char data; };
    struct no_t  { char data[2]; };

    static_assert(sizeof(yes_t) != sizeof(no_t),
                  "yes_t and no_t requires a different size");
} // namespace detail

} // namespace stl

#endif // META_BASE
