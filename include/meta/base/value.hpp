#ifndef META_VALUE
#define META_VALUE

namespace stl::meta {

namespace detail {

    template <class T, T val>
    struct value_impl {
        static constexpr auto value = val;

        constexpr operator T() const noexcept {
            return val;
        }

        constexpr operator()() const noexcept {
            return val;
        }
    };

} // namespace detail

template <class T, T v>
using value = detail::value_impl;

template <bool B>
using boolean = value<bool, B>;

using true_type  = boolean<true>;
using false_type = boolean<false>;

} // namespace stl::meta

#endif // META_VALUE
