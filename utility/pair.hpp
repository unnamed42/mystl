#ifndef UTILITY_PAIR
#define UTILITY_PAIR

#include "meta/bits/remove_reference.hpp"

#include "utility/bits/swap.hpp"
#include "utility/bits/forward.hpp"

namespace stl {

template <class T1, class T2>
struct pair {
private:
    using self = pair<T1, T2>;
public:
    T1 first;
    T2 second;

    constexpr pair() = default;

    constexpr pair(const T1 &f, const T2 &s) : first(f)      , second(s)       {}
    constexpr pair(const T1 &f, T2 &&s)      : first(f)      , second(move(s)) {}
    constexpr pair(T1 &&f, const T2 &s)      : first(move(f)), second(s)       {}
    constexpr pair(T1 &&f, T2 &&s)           : first(move(f)), second(move(s)) {}

    constexpr pair(const self &o)
        : pair(o.first, o.second) {}
    constexpr pair(self &&o)
        : pair(move(o.first), move(o.second)) {}

    constexpr void swap(self &o) {
        using stl::swap;
        swap(first, o.first);
        swap(second, o.second);
    }

    constexpr self& operator=(self o) noexcept {
        this->swap(o);
        return *this;
    }
};

template <class T1, class T2>
constexpr pair<remove_reference_t<T1>, remove_reference_t<T2>> make_pair(T1 &&t1, T2 &&t2) {
    return { forward<T1>(t1), forward<T2>(t2) };
}

template <class T1, class T2>
constexpr bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    if(lhs.first == rhs.first)
        return lhs.second < rhs.second;
    return lhs.first < rhs.first;
}

template <class T1, class T2>
constexpr bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
constexpr bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first != rhs.first || lhs.second != rhs.second;
}

template <class T1, class T2>
constexpr bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return rhs < lhs; }
template <class T1, class T2>
constexpr bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs > rhs); }
template <class T1, class T2>
constexpr bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs < rhs); }

} // namespace stl

#endif // UTILITY_PAIR
