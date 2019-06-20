#ifndef UTILITY_DETAIL_TUPLE_LEAF
#define UTILITY_DETAIL_TUPLE_LEAF

#include "meta/bits/enable_if.hpp"
#include "meta/bits/logic.hpp"
#include "meta/bits/is_same.hpp"
#include "meta/bits/declval.hpp"
#include "meta/bits/is_reference.hpp"
#include "meta/bits/is_constructible.hpp"
#include "meta/bits/remove_reference.hpp"

#include "utility/bits/swap.hpp"
#include "utility/bits/forward.hpp"
#include "utility/reference_wrapper.hpp"

namespace stl { namespace detail {

template <size_t Idx, class ValueType,
          bool Empty = __is_empty(ValueType) && !__is_final(ValueType)>
class tuple_leaf;

template <size_t I, class V, bool E>
inline constexpr void swap(tuple_leaf<I, V, E> &lhs, tuple_leaf<I, V, E> &rhs) {
    swap(lhs.get(), rhs.get());
}

template <size_t I, class V, bool E>
class tuple_leaf {
    V value;
public:
    constexpr tuple_leaf() : value() {
        static_assert(!is_reference_v<V>,
            "Attempt to default construct a reference element in tuple");
    }

    constexpr tuple_leaf(const tuple_leaf &t) : value(t.get()) {
        static_assert(!is_rvalue_reference_v<V>,
            "Cannot copy a tuple with rvalue reference member");
    }

    template < class T, class = enable_if_t<is_constructible_v<V, T>> >
    explicit constexpr tuple_leaf(T &&t) : value(stl::forward<T>(t)) {
        if constexpr (is_lvalue_reference_v<V>) {
            static_assert(or_v<
                not_<is_reference<T>>,
                and_<
                    is_lvalue_reference<V>,
                    or_<
                        is_lvalue_reference<T>,
                        is_same<remove_reference_t<T>,
                                reference_wrapper<remove_reference_t<V>>>
                    >
                >,
                and_<
                    is_rvalue_reference<V>,
                    not_<is_lvalue_reference<T>>
                >
            >,
            "Attempt to construct a reference tuple member with an rvalue");
        }
    }

    template <class T>
    explicit constexpr tuple_leaf(const tuple_leaf<I, T> &t)
        : value(t.get()) {}

    template <class T>
    constexpr tuple_leaf& operator=(T &&t) {
        value = forward<T>(t);
        return *this;
    }

    constexpr void swap(tuple_leaf &o) {
        using namespace stl;
        swap(value, o.value);
    }

    constexpr       V& get()       { return value; }
    constexpr const V& get() const { return value; }
};

// special case for empty member
template <size_t I, class V>
class tuple_leaf<I, V, true> : private V {
public:
    constexpr tuple_leaf() = default;

    constexpr tuple_leaf(const tuple_leaf &t) : V(t.get()) {
        static_assert(!is_rvalue_reference_v<V>,
                      "Cannot copy a tuple with rvalue reference member");
    }

    template <class T,
        class = enable_if_t<is_constructible_v<V, T>> >
    explicit constexpr tuple_leaf(T &&t) : V(forward<T>(t)) {}

    template <class T>
    explicit constexpr tuple_leaf(const tuple_leaf<I, T> &t)
        : V(t.get()) {}

    template <class T>
    constexpr tuple_leaf& operator=(T &&t) {
        get() = forward<T>(t);
        return *this;
    }

    constexpr void swap(tuple_leaf &t) {
        using namespace stl;
        swap(get(), t.get());
    }

    constexpr       V& get()       { return *static_cast<V*>(this); }
    constexpr const V& get() const { return *static_cast<V*>(this); }
};

}} // namespace detail

#endif // UTILITY_DETAIL_TUPLE_LEAF
