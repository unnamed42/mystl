#ifndef CONTAINER_ACCESS
#define CONTAINER_ACCESS

#include "def.hpp"
#include "iterator/reverse_iterator.hpp"

namespace stl {

template <class Container>
auto begin(Container &cont) { return cont.begin(); }
template <class Container>
auto end(Container &cont)   { return cont.end(); }

template <class Container>
auto begin(const Container &cont) { return cont.cbegin(); }
template <class Container>
auto end(const Container &cont)   { return cont.cend(); }

template <class T, size_t N>
T* begin(T (&arr)[N]) { return arr; }
template <class T, size_t N>
T* end(T (&arr)[N])   { return arr + N; }

template <class Container>
auto cbegin(const Container &cont) { return stl::begin(cont); }
template <class Container>
auto cend(const Container &cont)   { return stl::end(cont); }

template <class Container>
auto rbegin(Container &cont) { return cont.rbegin(); }
template <class Container>
auto rend(Container &cont)   { return cont.rend(); }

template <class Container>
auto rbegin(const Container &cont) { return cont.crbegin(); }
template <class Container>
auto rend(const Container &cont)   { return cont.crend(); }

template <class T, size_t N>
reverse_iterator<T*> rbegin(T (&arr)[N]) { return { stl::end(arr) }; }
template <class T, size_t N>
reverse_iterator<T*> rend(T (&arr)[N])   { return { stl::begin(arr) }; }

template <class Container>
auto crbegin(const Container &cont) { return stl::rbegin(cont); }
template <class Container>
auto crend(const Container &cont)   { return stl::rend(cont); }

template <class Container>
auto size(const Container &cont) { return cont.size(); }

} // namespace stl

#endif // CONTAINER_ACCESS
