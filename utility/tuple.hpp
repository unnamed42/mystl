#ifndef UTILITY_TUPLE
#define UTILITY_TUPLE

#include "meta/cvref.hpp"
#include "meta/check.hpp"
#include "meta/sfinae.hpp"
#include "meta/constructible.hpp"

#include "utility/swap.hpp"
#include "utility/declval.hpp"
#include "utility/forward.hpp"
#include "utility/reference_wrapper.hpp"

// std::is_empty and std::is_final is compiler intrinsics
#include <type_traits>

namespace stl {

namespace detail {



} // namespace detail

} // namespace stl

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
