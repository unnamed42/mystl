#ifndef UTILITY_PAIR
#define UTILITY_PAIR

#include "meta/ref.hpp"

#include "utility/swap.hpp"
#include "utility/forward.hpp"

namespace stl {

template <class T1, class T2>
struct pair {
private:
    using self = pair<T1, T2>;
public:
    T1 first;
    T2 second;

    pair() = default;

    pair(const T1 &f, const T2 &s) : first(f)      , second(s)       {}
    pair(const T1 &f, T2 &&s)      : first(f)      , second(move(s)) {}
    pair(T1 &&f, const T2 &s)      : first(move(f)), second(s)       {}
    pair(T1 &&f, T2 &&s)           : first(move(f)), second(move(s)) {}

    pair(const self &o)
        : pair(o.first, o.second) {}
    pair(self &&o)
        : pair(move(o.first), move(o.second)) {}

    void swap(self &o) {
        using swap;
        swap(first, o.first);
        swap(second, o.second);
    }

    self& operator=(self o) noexcept {
        this->swap(o);
        return *this;
    }
};

template <class T1, class T2>
pair<remove_reference_t<T1>, remove_reference_t<T2>> make_pair(T1 &&t1, T2 &&t2) {
    return { forward<T1>(t1), forward<T2>(t2) };
}

template <class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    if(lhs.first == rhs.first)
        return lhs.second < rhs.second;
    return lhs.first < rhs.first;
}

template <class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first != rhs.first || lhs.second != rhs.second;
}

template <class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return rhs < lhs; }
template <class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs > rhs); }
template <class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return !(lhs < rhs); }

} // namespace stl

#endif // UTILITY_PAIR
