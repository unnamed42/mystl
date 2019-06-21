#ifndef META_BITS_IS_COPY_ASSIGNABLE
#define META_BITS_IS_COPY_ASSIGNABLE

#include "meta/bits/is_assignable.hpp"
#include "meta/bits/add_reference.hpp"

namespace stl {

template <class T>
struct is_copy_assignable
    : is_assignable<add_lvalue_reference_t<T>,
                    add_lvalue_reference_t<const T>> {};

} // namespace stl

#endif // META_BITS_IS_COPY_ASSIGNABLE
