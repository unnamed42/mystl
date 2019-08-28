#ifndef CONTAINER_ARRAY
#define CONTAINER_ARRAY

#include "def.hpp"

#include "meta/bits/enable_if.hpp"

#include "utility/bits/forward.hpp"

#include "algorithm/fill.hpp"
#include "algorithm/copy.hpp"

namespace stl {

template <class T, size_t N>
class array {
    T values[N];
public:
    using iterator       = T*;
    using const_iterator = const T*;
public:
    constexpr array()             = default;
    constexpr array(const array&) = default;
    constexpr array(array&&)      = default;
             ~array()             = default;

    constexpr array& operator=(const array&) = default;
    constexpr array& operator=(array&&)      = default;

    template <class ...Ts,
              class = enable_if_t<sizeof...(Ts) == N>>
    constexpr array(Ts&& ...ts) : values(forward<Ts>(ts)...) {}

    constexpr       T& operator[](size_t idx)       noexcept { return values[idx]; }
    constexpr const T& operator[](size_t idx) const noexcept { return values[idx]; }

    constexpr T* begin() noexcept { return values; }
    constexpr T* end()   noexcept { return values + N; }

    constexpr const T* cbegin() const noexcept { return values; }
    constexpr const T* cend()   const noexcept { return values + N; }

    constexpr       T& front()       noexcept { return values[0]; }
    constexpr const T& front() const noexcept { return values[0]; }
    constexpr       T& back()        noexcept { return values[N - 1]; }
    constexpr const T& back()  const noexcept { return values[N - 1]; }

    constexpr       T* data()       noexcept { return values; }
    constexpr const T* data() const noexcept { return values; }

    constexpr size_t size() const noexcept { return N; }

    template <class U>
    constexpr void fill(const U &u) {
        fill(begin(), end(), u);
    }

    template <class U>
    constexpr void swap(array<U, N> &arr) {
        for(size_t i = 0; i < N; ++i) {
            using stl::swap;
            swap(this->operator[](i), arr[i]);
        }
    }
};

} // namespace stl

#endif // CONTAINER_ARRAY
