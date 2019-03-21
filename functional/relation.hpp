#ifndef FUNCTIONAL_RELATION
#define FUNCTIONAL_RELATION

#include "functional/logic.hpp"

namespace stl {

namespace detail {
    template <template <class> class Relation, class T>
    struct not_ {
        bool operator()(const T &lhs, const T &rhs) const {
            return !Relation<T>{}(lhs, rhs);
        }
    };

    template <template <class> class Relation>
    struct not_<Relation, void> {
        template <class T>
        bool operator()(const T &lhs, const T &rhs) const {
            return !Relation<T>{}(lhs, rhs);
        }
    };
} // namespace detail

template <class T = void>
struct equal {
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs == rhs;
    }
};

template <> struct equal<void> {
    template <class T>
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs == rhs;
    }
};

template <class T = void>
struct less {
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs < rhs;
    }
};

template <> struct less<void> {
    template <class T>
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs < rhs;
    }
};

template <class T = void>
struct greater {
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs > rhs;
    }
};

template <> struct greater<void> {
    template <class T>
    bool operator()(const T &lhs, const T &rhs) const {
        return lhs > rhs;
    }
};

template <class T = void>
using not_equal = detail::not_<equal, T>;

template <class T = void>
using less_equal = detail::not_<greater, T>;

template <class T = void>
using greater_equal = detail::not_<less, T>;

} // namespace stl

#endif // FUNCTIONAL_RELATION
