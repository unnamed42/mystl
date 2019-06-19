#ifndef META_BITS_ALIGNED_STORAGE
#define META_BITS_ALIGNED_STORAGE

#include "def.hpp"

namespace stl {

template <size_t Size, size_t Align>
struct aligned_storage {
    struct type {
        alignas(Align) unsigned char data[Size];
    };
};

template <size_t Size, size_t Align>
using aligned_storage_t = typename aligned_storage<Size, Align>::type;

} // namespace stl

#endif // META_BITS_ALIGNED_STORAGE
