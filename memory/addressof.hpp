#ifndef MEMORY_ADDRESSOF
#define MEMORY_ADDRESSOF

namespace stl {

template <class T>
T* addressof(T &t) {
    return reinterpret_cast<T*>(
        &const_cast<char&>(
            reinterpret_cast<const volatile char&>(t)
        )
    );
}

} // namespace stl

#endif // MEMORY_ADDRESSOF
