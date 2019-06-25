#ifndef FUNCTIONAL_BITS_MULTI_APPLY
#define FUNCTIONAL_BITS_MULTI_APPLY

#include "def.hpp"

#include "meta/bits/identity.hpp"
#include "meta/bits/condition.hpp"
#include "meta/bits/sequence.hpp"
#include "meta/bits/concat.hpp"
#include "meta/bits/remove_reference.hpp"

#include "utility/tuple.hpp"
#include "utility/bits/tuple_index.hpp"
#include "utility/bits/forward.hpp"

#include "functional/bits/invoke.hpp"

#include "container/array.hpp"

namespace stl {

namespace detail {

    template <size_t N, size_t E> struct argument_indices {
        static constexpr auto N = N;
        static constexpr auto E = E;
    };

    template <size_t, class, class> struct tuple_to_argument {};

    template <size_t C, size_t ...Idx, class Tuple>
    struct tuple_to_argument<C, index_sequence<Idx...>, Tuple>
        : types<argument_indices<C, Idx>...> {};

    template <class Idx, class TofTuples>
    struct fuck1 {};

    template <size_t ...Idx, class ...Tuples>
    struct fuck1<index_sequence<Idx...>, types<Tuples...>>
        : types<condition_t<>...> {};

    template <class ...Tuples>
    struct make_tuples_indices {};

    // TODO: implement indices with template meta programming
    template <size_t S, class ...Ts>
    constexpr auto make_indices() {
        constexpr size_t sizes[] = {
            tuple_size_v<remove_reference_t<Ts>>...
        };
        constexpr array<pair<size_t, size_t>, S> ret;
        constexpr auto tup = ret.begin();
        for(constexpr size_t i=0; i<sizeof...(Ts); ++i) {
            if(sizes[0] == 0)
                continue;
            for(constexpr size_t j=0; j<sizes[i]; ++j) {
                tup->first = i;
                tup->second = j;
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
