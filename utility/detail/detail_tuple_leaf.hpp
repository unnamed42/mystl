#ifndef UTILITY_DETAIL_TUPLE_LEAF
#define UTILITY_DETAIL_TUPLE_LEAF

#include "meta/cvref.hpp"
#include "meta/check.hpp"
#include "meta/sfinae.hpp"
#include "meta/constructible.hpp"

#include "utility/swap.hpp"
#include "utility/declval.hpp"
#include "utility/forward.hpp"
#include "utility/reference_wrapper.hpp"

#include <type_traits>

namespace stl { namespace detail {

template <size_t Idx, class ValueType,
          bool Empty = std::is_empty_v<ValueType> && !std::is_final_v<ValueType> >
class tuple_leaf;

template <size_t I, class V, bool E>
inline void swap(tuple_leaf<I, V, E> &lhs, tuple_leaf<I, V, E> &rhs) {
    swap(lhs.get(), rhs.get());
}

template <size_t I, class V, bool E>
class tuple_leaf {
    V value;
public:
    tuple_leaf() : value() {
        static_assert(!is_reference_v<V>,
            "Attempt to default construct a reference element in tuple");
    }

    tuple_leaf(const tuple_leaf &t) : value(t.get()) {
        static_assert(!is_rvalue_reference_v<V>,
            "Cannot copy a tuple with rvalue reference member");
    }

    template < class T, class = enable_if_t<is_constructible_v<V, T>> >
    explicit tuple_leaf(T &&t) : value(forward<T>(t)) {
        static_assert(!is_reference_v<T> ||
            (is_lvalue_reference_v<V> && (
                (is_lvalue_reference_v<T> ||
                 is_same_v<remove_reference_t<T>,
                           reference_wrapper<remove_reference_t<V>> >))
            ) ||
            (is_rvalue_reference_v<V> && !is_lvalue_reference_v<T>),
            "Attempt to construct a reference tuple member with an rvalue");
    }

    template <class T>
    explicit tuple_leaf(const tuple_leaf<I, T> &t)
        : value(t.get()) {}

    template <class T>
    tuple_leaf& operator=(T &&t) {
        value = forward<T>(t);
        return *this;
    }

    void swap(tuple_leaf &o) {
        using namespace stl;
        using namespace std;
        swap(value, o.value);
    }

          V& get()       { return value; }
    const V& get() const { return value; }
};

// special case for empty member
template <size_t I, class V>
class tuple_leaf<I, V, true> : private V {
public:
    tuple_leaf() = default;

    tuple_leaf(const tuple_leaf &t) : V(t.get()) {
        static_assert(!is_rvalue_reference_v<V>,
                      "Cannot copy a tuple with rvalue reference member");
    }

    template <class T,
        class = enable_if_t<is_constructible_v<V, T>> >
    explicit tuple_leaf(T &&t) : V(forward<T>(t)) {}

    template <class T>
    explicit tuple_leaf(const tuple_leaf<I, T> &t)
        : V(t.get()) {}

    template <class T>
    tuple_leaf& operator=(T &&t) {
        get() = forward<T>(t);
        return *this;
    }

    void swap(tuple_leaf &t) {
        using namespace stl;
        using namespace std;
        swap(get(), t.get());
    }

          V& get()       { return *static_cast<V*>(this); }
    const V& get() const { return *static_cast<V*>(this); }
};

}} // namespace detail

#endif // UTILITY_DETAIL_TUPLE_LEAF
