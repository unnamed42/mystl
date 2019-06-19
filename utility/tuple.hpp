#ifndef UTILITY_TUPLE
#define UTILITY_TUPLE

#include "utility/bits/detail/tuple.hpp"

// c++17 struture binding support

#include <tuple>

namespace std {

    /* template <class ...Args> */
    /* struct tuple_size<stl::tuple<Args...>> */
    /*     : integral_constant<size_t, sizeof...(Args)> {}; */

    /* template <size_t N, class ...Args> */
    /* struct tuple_element<N, stl::tuple<Args...>> { */
    /* private: */
    /*     using tupl = stl::tuple<Args...>; */
    /* public: */
    /*     using type = decltype(declval<tupl>().template get<N>()); */
    /* }; */

}

#endif // UTILITY_TUPLE
