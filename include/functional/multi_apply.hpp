#ifndef FUNCTIONAL_BITS_MULTI_APPLY
#define FUNCTIONAL_BITS_MULTI_APPLY

#include "def.hpp"

#include "meta/bits/identity.hpp"
#include "meta/bits/condition.hpp"
#include "meta/bits/sequence.hpp"
#include "meta/bits/remove_reference.hpp"
#include "meta/bits/concat.hpp"
#include "meta/bits/flatten.hpp"

#include "utility/tuple.hpp"
#include "utility/bits/tuple_types.hpp"
#include "utility/bits/tuple_index.hpp"
#include "utility/bits/forward.hpp"

#include "functional/bits/invoke.hpp"

#include "container/array.hpp"

namespace stl {

namespace detail {

    template <size_t N, size_t E> struct argument_index;

    template <size_t C, class IdxSequence>
    struct make_indices_helper {};

    template <size_t C, size_t ...Idx>
    struct make_indices_helper<C, index_sequence<Idx...>>
        : types<argument_index<C, Idx>...> {};

    template <class IdxSequence, class TypeOfTuples>
    struct make_indices_impl {};

    template <size_t ...Idx, class ...Tuples>
    struct make_indices_impl<index_sequence<Idx...>, types<Tuples...>>
        : concat<typename make_indices_helper<Idx,
                    typename get_tuple_types<Tuples>::type>::type...> {};

    template <class IdxSequence>
    struct make_indices {};

    template <size_t ...Ns, size_t ...Es>
    struct make_indices<types<argument_index<Ns, Es>...>> {
        using tuple_index_t = index_sequence<Ns...>;
        using elem_index_t = index_sequence<Es...>;
    };

    // TODO: implement indices with template meta programming
//     template <size_t S, class ...Ts>
//     constexpr auto make_indices() {
//         constexpr size_t sizes[] = {
//             tuple_size_v<remove_reference_t<Ts>>...
//         };
//         constexpr array<pair<size_t, size_t>, S> ret;
//         constexpr auto tup = ret.begin();
//         for(constexpr size_t i=0; i<sizeof...(Ts); ++i) {
//             if(sizes[0] == 0)
//                 continue;
//             for(constexpr size_t j=0; j<sizes[i]; ++j) {
//                 tup->first = i;
//                 tup->second = j;
//             }
//         }
//         return ret;
//     }

    template <class F, class ...Tuples, size_t ...OuterIdx, size_t ...InnerIdx>
    constexpr decltype(auto) multi_apply_impl(index_sequence<OuterIdx...>,
                                              index_sequence<InnerIdx...>,
                                              F &&f, tuple<Tuples...> &&t) {
        return invoke(forward<F>(f), get<InnerIdx>(get<OuterIdx>(move(t)))...);
    }

    template <class F, class ...Tuples, size_t ...Idx>
    constexpr decltype(auto) multi_apply_impl(index_sequence<Idx...>,
                                              F &&f, tuple<Tuples...> &&t) {
        using argument_indices = make_indices_impl<make_index_sequence_t<sizeof...(Tuples)>,
                                                   types<Tuples...>>;
        using indices_t = make_indices<typename argument_indices::type>;
//         constexpr auto indices = make_indices<sizeof...(Idx), Tuples...>();
        return multi_apply_impl(typename indices_t::tuple_index_t{},
                                typename indices_t::elem_index_t{},
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
