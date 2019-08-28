#ifndef UTILITY_TUPLE
#define UTILITY_TUPLE

#include "meta/bits/is_same.hpp"
#include "meta/bits/enable_if.hpp"
#include "meta/bits/copy_cvref.hpp"
#include "meta/bits/remove_cvref.hpp"
#include "meta/bits/index_sequence.hpp"
#include "meta/bits/is_instance_of.hpp"
#include "meta/bits/nth_element.hpp"

#include "utility/bits/forward.hpp"
#include "utility/bits/forward_like.hpp"
#include "utility/bits/tuple_size.hpp"
#include "utility/bits/tuple_types.hpp"
#include "utility/bits/tuple_element.hpp"
#include "utility/bits/make_tuple.hpp"
#include "utility/bits/get_fwd.hpp"
#include "utility/bits/detail/tuple_impl.hpp"
#include "utility/bits/detail/tuple_traits.hpp"
#include "utility/bits/detail/tuple_relational.hpp"

namespace stl {

template <class, class> class pair;

template <class ...Ts>
class tuple {
    friend struct detail::get_impl<tuple<Ts...>>;

    using impl_t = detail::tuple_impl<make_index_sequence_t<sizeof...(Ts)>, Ts...>;
private:
    impl_t impl;
private:
    constexpr       impl_t& data()       noexcept { return impl; }
    constexpr const impl_t& data() const noexcept { return impl; }
public:
    constexpr tuple() : impl() {}

    constexpr tuple(const Ts& ...ts)
        : impl(make_index_sequence_t<sizeof...(Ts)>{},
               make_tuple_types_t<tuple, sizeof...(Ts)>{},
               make_index_sequence_t<0>{},
               make_tuple_types_t<tuple, 0>{},
               ts...) {}

    template <class ...Us, bool Larger = sizeof...(Us) <= sizeof...(Ts),
              class = enable_if_t<Larger && detail::tuple_convertible_v<
                  make_tuple_types_t<tuple<Us...>>,
                  make_tuple_types_t<tuple, Larger ? sizeof...(Us) : sizeof...(Ts)>> >
             >
    constexpr tuple(Us&& ...us)
        : impl(make_index_sequence_t<sizeof...(Us)>{},
               make_tuple_types_t<tuple, sizeof...(Ts)>{},
               make_index_sequence_t<sizeof...(Ts), sizeof...(Us)>{},
               make_tuple_types_t<tuple, sizeof...(Ts)>{},
               forward<Us>(us)...) {}

    template <class Tuple, class = enable_if_t<
        detail::tuple_convertible_v<Tuple, tuple>
    >>
    constexpr tuple(Tuple &&t) : impl(forward<Tuple>(t)) {}

    template <class Tuple, class = enable_if_t<
        detail::tuple_assignable_v<tuple, Tuple>
    >>
    constexpr tuple& operator=(tuple &&t) {
        impl = forward<Tuple>(t);
        return *this;
    }

    constexpr void swap(tuple &t) {
        impl.swap(t.impl);
    }
};

template <> class tuple<> {
public:
    constexpr tuple() = default;

    template <class Tuple, class = enable_if_t<
        detail::tuple_convertible_v<Tuple, tuple>
    >>
    constexpr tuple(Tuple&&) {}

    template <class Tuple, class = enable_if_t<
        detail::tuple_assignable_v<tuple, Tuple>
    >>
    constexpr tuple& operator=(Tuple &&) { return *this; }

    constexpr void swap(tuple&) {}
};

template <class T>
tuple(T) -> tuple<T>;

template <class ...Ts>
tuple(Ts...) -> tuple<Ts...>;

template <class T, class U>
tuple(pair<T, U>) -> tuple<T, U>;

// get for tuple<Ts...>

namespace detail {

    template <class ...Ts>
    struct get_impl<tuple<Ts...>> {
        template <size_t I, class Tuple, class = enable_if_t<
            is_same_v<remove_cvref_t<Tuple>, tuple<Ts...>>>
        >
        static constexpr decltype(auto) get(Tuple &&t) {
            using tuple_t = remove_reference_t<Tuple>;
            using types_t = typename get_tuple_types<tuple_t>::type;
            using elem_t = typename nth_element<I, types_t>::type;
            using leaf_t = copy_cv_t<tuple_leaf<I, elem_t>, tuple_t>;

            return forward_like<Tuple>(static_cast<leaf_t&>(t.impl).get());
        }
    };

}

// comparators

template <class ...Ts, class ...Us>
inline constexpr bool operator==(const tuple<Ts...> &lhs, const tuple<Us...> &rhs) {
    return detail::tuple_equal<sizeof...(Ts)>{}(lhs, rhs);
}

template <class ...Ts, class ...Us>
inline constexpr bool operator!=(const tuple<Ts...> &lhs, const tuple<Us...> &rhs) {
    return !(lhs == rhs);
}

template <class ...Ts, class ...Us>
inline constexpr bool operator<(const tuple<Ts...> &lhs, const tuple<Us...> &rhs) {
    return detail::tuple_less<sizeof...(Ts)>{}(lhs, rhs);
}

template <class ...Ts, class ...Us>
inline constexpr bool operator>(const tuple<Ts...> &lhs, const tuple<Us...> &rhs) {
    return rhs < lhs;
}

template <class ...Ts, class ...Us>
inline constexpr bool operator<=(const tuple<Ts...> &lhs, const tuple<Us...> &rhs) {
    return !(lhs > rhs);
}

template <class ...Ts, class ...Us>
inline constexpr bool operator>=(const tuple<Ts...> &lhs, const tuple<Us...> &rhs) {
    return !(lhs < rhs);
}

} // namespace stl


// c++17 struture binding support
#include <tuple>

namespace std {

// tuple_size

template <class ...Ts>
struct tuple_size<stl::tuple<Ts...>>
    : integral_constant<size_t, sizeof...(Ts)> {};

template <class ...Ts>
struct tuple_size<const stl::tuple<Ts...>>
    : integral_constant<size_t, sizeof...(Ts)> {};

template <class ...Ts>
struct tuple_size<volatile stl::tuple<Ts...>>
    : integral_constant<size_t, sizeof...(Ts)> {};

template <class ...Ts>
struct tuple_size<const volatile stl::tuple<Ts...>>
    : integral_constant<size_t, sizeof...(Ts)> {};

// tuple_element

template <size_t I, class ...Ts>
struct tuple_element<I, stl::tuple<Ts...>>
    : stl::tuple_element<I, stl::tuple<Ts...>> {};

template <size_t I, class ...Ts>
struct tuple_element<I, const stl::tuple<Ts...>>
    : stl::tuple_element<I, const stl::tuple<Ts...>> {};

template <size_t I, class ...Ts>
struct tuple_element<I, volatile stl::tuple<Ts...>>
    : stl::tuple_element<I, volatile stl::tuple<Ts...>> {};

template <size_t I, class ...Ts>
struct tuple_element<I, const volatile stl::tuple<Ts...>>
    : stl::tuple_element<I, const volatile stl::tuple<Ts...>> {};

using stl::get;

}

#endif // UTILITY_TUPLE
