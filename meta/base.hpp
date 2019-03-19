#ifndef META_BASE
#define META_BASE

namespace rubbish {

template <class T, T t>
struct constant { static constexpr auto value = t; };

using true_type  = constant<bool, true>;
using false_type = constant<bool, false>;

namespace detail {
    using yes_t = char[1];
    using no_t  = char[2];

    static_assert(sizeof(yes_t) != sizeof(no_t),
                  "yes_t and no_t requires a different size");
} // namespace detail

} // namespace rubbish

#endif // META_BASE
