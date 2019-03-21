#ifndef UTILITY_TUPLE
#define UTILITY_TUPLE

#include "utility/forward.hpp"
#include "meta/index_sequence.hpp"

namespace stl {

namespace detail {
    template <unsigned, class...>
    struct nth_type ;

    template <unsigned N, class First, class ...Rest>
    struct nth_type<N, First, Rest...> : nth_type<N-1, Rest...> {};

    template <class First, class ...Rest>
    struct nth_type<0, First, Rest...> { using type = First; };

    template <unsigned Id, class T>
    struct tuple_elem {
        T elem;

        tuple_elem(T val)
            : elem(move(val)) {}

              T& get()       { return elem; }
        const T& get() const { return elem; }
    };

    template <class Sequence, class ...Args>
    struct tuple_impl ;

    template <unsigned ...Idx, class ...Args>
    struct tuple_impl<stl::index_sequence<Idx...>, Args...>
        : tuple_elem<Idx, Args>... {
    private:
        template <unsigned N> using pick = typename nth_type<N, Args...>::type;
        template <unsigned N> using elem = tuple_elem<N, pick<N>>;
    public:
        template <unsigned Index>
              pick<Index>& get()       { return elem<Index>::get(); }

        template <unsigned Index>
        const pick<Index>& get() const { return elem<Index>::get(); }
    };
} // namespace detail

template <class ...Args>
struct tuple : detail::tuple_impl<make_index_sequence_t<sizeof...(Args)>, Args...> {

};

} // namespace stl

// c++17 struture binding support

#include <tuple>

namespace std {

    template <class ...Args>
    struct tuple_size<stl::tuple<Args...>>
        : integral_constant<size_t, sizeof...(Args)> {};

    template <size_t N, class ...Args>
    struct tuple_element<N, stl::tuple<Args...>> {
    private:
        using tupl = stl::tuple<Args...>;
    public:
        using type = decltype(declval<tupl>().template get<N>());
    };

}

#endif // UTILITY_TUPLE
