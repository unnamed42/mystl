#ifndef META_CONCAT
#define META_CONCAT

namespace stl::meta {

namespace detail {

    template <class, class> struct concat_two {};

    template <template <class...> class Types, class ...Lhs, class ...Rhs>
    struct concat_two<Types<Lhs...>, Types<Rhs...>>
        : Types<Lhs..., Rhs...> {};

} // namespace ns

template <class...> struct concat;

template <template <class...> class Types, class ...Ts>
struct concat<Types<Ts...>> : Types<Ts...> {};

template <class T1, class T2, class ...Tn>
struct concat<T1, T2, Tn...> : concat<typename detail::concat_two<T1, T2>::type, Tn...> {};

template <class ...Ts>
using concat_t = typename concat<Ts...>::type;

} // namespace stl::meta

#endif // META_CONCAT
