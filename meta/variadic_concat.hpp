#ifndef META_VARIADIC_CONCAT
#define META_VARIADIC_CONCAT

namespace stl {

template <class, class>
struct variadic_concat {};

template <template <class...> class Variadic, class ...Args1, class ...Args2>
struct variadic_concat<Variadic<Args1...>, Variadic<Args2...>> {
    using type = Variadic<Args1..., Args2...>;
};

template <class T, template <T...> class Sequence, T ...args1, T ...args2>
struct variadic_concat<Sequence<args1...>, Sequence<args2...>> {
    using type = Sequence<args1..., args2...>;
};

} // namespace stl

#endif // META_VARIADIC_CONCAT
