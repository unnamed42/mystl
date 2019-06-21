#ifndef FUNCTIONAL_BITS_MULTI_APPLY
#define FUNCTIONAL_BITS_MULTI_APPLY

#include "def.hpp"

#include "meta/bits/identity.hpp"
#include "meta/bits/condition.hpp"
#include "meta/bits/sequence.hpp"
#include "meta/bits/concat.hpp"
#include "meta/bits/remove_reference.hpp"
#include "meta/bits/types_filter.hpp"

#include "utility/tuple.hpp"
#include "utility/bits/tuple_index.hpp"
#include "utility/bits/forward.hpp"

#include "functional/bits/invoke.hpp"

#include "container/array.hpp"

namespace stl {

namespace detail {

    // the argument is the M-th element of the N-th tuple
    template <size_t N, size_t M> struct tuple_argument {};

    // convert tuple type to a sequence of (N, M) tuple_argument types

    template <size_t Curr, class Tuple>
    struct tuple_to_indices
        : tuple_to_indices<Curr, tuple_index_t<remove_reference_t<Tuple>>> {};

    template <size_t Curr, size_t ...Idx>
    struct tuple_to_indices<Curr, index_sequence<Idx...>>
        : identity<types<tuple_argument<Curr, Idx>...>> {};

    // remove empty tuples

    template <size_t C, class, class> struct valid_tuples;

    template <size_t C, class ...Indices, class T, class ...Tuples>
    struct valid_tuples<C, types<Indices...>, types<T, Tuples...>>
        : condition_t<tuple_size_v<T> != 0,
                      valid_tuples<C + 1, types<Indices..., tuple_to_indices<C, T>>, types<Tuples...>>,
                      valid_tuples<C + 1, types<ValidTuples...>                    , types<Tuples...>>
        > {};

    template <size_t C, class ...Indices>
    struct valid_tuples<C, types<Indices...>, types<>>
        : types<Indices...> {};

    // expand tuple indices to tuple_argument

    template <class> struct expand_indices;

    template <class Indices...>
    struct expand_indices


    template <size_t S, class ...Ts>
    constexpr auto make_indices() {
        constexpr size_t sizes[] = {
            tuple_size_v<remove_reference_t<Ts>>...
        };

        array<pair<size_t, size_t>, S> ret;

        auto tup = ret.begin();
        for(size_t i=0; i<sizeof...(Ts); ++i) {
            for(size_t j=0; j<sizes[i]; ++j) {
                tup->first = i;
                tup->second = j;
            }
        }

        using arr_t = array<size_t, S>;
        pair<arr_t, arr_t> ret{};
        for(size_t c = 0, i = 0; i<sizeof...(Ts); ++i) {
            for(size_t j=0; j<sizes[i]; ++j, ++c) {
                ret.first[c] = i;
                ret.second[c] = j;
            }
        }
        return ret;
    }

    template <class F, class ...Tuples, size_t ...OuterIdx, size_t ...InnerIdx>
    constexpr decltype(auto) multi_apply_impl(index_sequence<OuterIdx...>,
                                              index_sequence<InnerIdx...>,
                                              F &&f, tuple<Tuples...> &&t) {
        return invoke(forward<F>(f), get<InnerIdx>(get<OuterIdx>(move(t)))...);
    }

    template <class F, class ...Tuples, size_t ...Idx>
    constexpr decltype(auto) multi_apply_impl(index_sequence<Idx...>,
                                              F &&f, tuple<Tuples...> &&t) {
        constexpr auto indices = make_indices<sizeof...(Idx), Tuples...>();
        return multi_apply_impl(index_sequence<indices.first[Idx]...>{},
                                index_sequence<indices.second[Idx]...>{},
                                forward<F>(f), move(t));
    }

} // namespace detail

template <class F, class ...Tuples>
constexpr decltype(auto) multi_apply(F &&f, Tuples&& ...ts) {
    constexpr auto sizes = (0U + ... + tuple_size_v<remove_reference_t<Tuples>>);
    if constexpr (sizes != 0)
        return detail::multi_apply_impl(make_index_sequence_t<sizes>{},
                                        forward<F>(f),
                                        forward_as_tuple(forward<Tuples>(ts)...));
    else
        return forward<F>(f)();
}

} // namespace stl

#endif // FUNCTIONAL_BITS_MULTI_APPLY
