#ifndef UTILITY_BITS_ADDRESSOF
#define UTILITY_BITS_ADDRESSOF

namespace stl {

template <class T>
T* addressof(T &arg) {
    return reinterpret_cast<T*>(
        &const_cast<char&>(reinterpret_cast<const volatile char&>(arg))
    );
}

} // namespace stl

#endif // UTILITY_BITS_ADDRESSOF
