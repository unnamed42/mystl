#ifndef META_COPY_REF
#define META_COPY_REF

#include "meta/bits/identity.hpp"
#include "meta/bits/add_reference.hpp"

namespace stl {

template <class T, class Source>
struct copy_ref : identity<T> {};

template <class T, class S>
struct copy_ref<T, S&> : add_lvalue_reference<T> {};

template <class T, class S>
struct copy_ref<T, S&&> : add_rvalue_reference<T> {};

template <class T, class S>
using copy_ref_t = typename copy_ref<T, S>::type;

} // namespace stl

#endif // META_COPY_REF
