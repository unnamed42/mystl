#ifndef META_COPY_CV
#define META_COPY_CV

#include "meta/bits/identity.hpp"

namespace stl {

template <class T, class Source>
struct copy_cv : identity<T> {};

template <class T, class S>
struct copy_cv<T, const S> : identity<const T> {};

template <class T, class S>
struct copy_cv<T, volatile S> : identity<volatile T> {};

template <class T, class S>
struct copy_cv<T, const volatile S> : identity<const volatile T> {};

template <class T, class S>
using copy_cv_t = typename copy_cv<T, S>::type;

} // namespace stl

#endif // META_COPY_CV
