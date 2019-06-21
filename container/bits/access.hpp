#ifndef CONTAINER_BITS_ACCESS
#define CONTAINER_BITS_ACCESS

#include "def.hpp"

#include "iterator/reverse_iterator.hpp"

namespace stl {

template <class Container>
constexpr auto begin(Container &cont) { return cont.begin(); }
template <class Container>
constexpr auto end(Container &cont)   { return cont.end(); }

template <class Container>
constexpr auto begin(const Container &cont) { return cont.cbegin(); }
template <class Container>
constexpr auto end(const Container &cont)   { return cont.cend(); }

template <class T, size_t N>
T* begin(T (&arr)[N]) { return arr; }
template <class T, size_t N>
T* end(T (&arr)[N])   { return arr + N; }

template <class Container>
constexpr auto cbegin(const Container &cont) { return begin(cont); }
template <class Container>
constexpr auto cend(const Container &cont)   { return end(cont); }

template <class Container>
constexpr auto rbegin(Container &cont) { return cont.rbegin(); }
template <class Container>
constexpr auto rend(Container &cont)   { return cont.rend(); }

template <class Container>
constexpr auto rbegin(const Container &cont) { return cont.crbegin(); }
template <class Container>
constexpr auto rend(const Container &cont)   { return cont.crend(); }

template <class T, size_t N>
constexpr reverse_iterator<T*> rbegin(T (&arr)[N]) { return { end(arr) }; }
template <class T, size_t N>
constexpr reverse_iterator<T*> rend(T (&arr)[N])   { return { begin(arr) }; }

template <class Container>
constexpr auto crbegin(const Container &cont) { return rbegin(cont); }
template <class Container>
constexpr auto crend(const Container &cont)   { return rend(cont); }

template <class Container>
constexpr auto size(const Container &cont) { return cont.size(); }

} // namespace stl

#endif // CONTAINER_BITS_ACCESS
