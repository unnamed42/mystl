#ifndef META_TYPE_LIST
#define META_TYPE_LIST

#include "meta/condition.hpp"
#include "meta/variadic_concat.hpp"

namespace stl {

struct null_type {};

template <class T, class N>
struct type_list {
    using type = T;
    using next = N;
};

template <class...>
struct make_type_list {};

template <class T>
struct make_type_list<T> {
    using type = type_list<T, null_type>;
};

template <class First, class ...Rest>
struct make_type_list<First, Rest...> {
    using type = type_list<First, typename make_type_list<Rest...>::type>;
};

template <class ...Args>
using make_type_list_t = typename make_type_list<Args...>::type;

template <class List>
struct type_list_length {};

template <class T>
struct type_list_length<type_list<T, null_type>> {
    static constexpr auto value = 1;
};

template <class T, class N>
struct type_list_length<type_list<T, N>> {
    static constexpr auto value = 1 + type_list_length<N>::value;
};

template <class...>
struct type_list_flatten {};

template <class T>
struct type_list_flatten<type_list<T, null_type>> {
    using type = type_list_flatten<T>;
};

template <class T, class N>
struct type_list_flatten<type_list<T, N>> {
private:
    using rest = typename type_list_flatten<N>::type;
public:
    using type = typename variadic_concat<type_list_flatten<T>, rest>::type;
};

template <class List>
using type_list_flatten_t = typename type_list_flatten<List>::type;

namespace detail {

    template <class List, template <class> class PropertyExtractor>
    struct type_list_max_type {};

    template <class T, template <class> class PE>
    struct type_list_max_type<type_list<T, null_type>, PE> {
        using type = T;
    };

    template <class T, class N, template <class> class PE>
    struct type_list_max_type<type_list<T, N>, PE> {
    private:
        using rest = typename type_list_max_type<N, PE>::type;
    public:
        using type = condition_t<(PE<T>::value > PE<rest>::value), T, rest>;
    };

    template <class T>
    struct size_of { static constexpr auto value = sizeof(T); };

    template <class T>
    struct align_of { static constexpr auto value = alignof(T); };

} // namespace detail

template <class List>
using type_list_size_max_t = typename detail::type_list_max_type<List, detail::size_of>::type;

template <class List>
using type_list_align_max_t = typename detail::type_list_max_type<List, detail::align_of>::type;

} // namespace stl

#endif // META_TYPE_LIST
