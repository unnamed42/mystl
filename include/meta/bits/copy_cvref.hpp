#ifndef META_BITS_COPY_CVREF
#define META_BITS_COPY_CVREF

#include "meta/bits/copy_cv.hpp"
#include "meta/bits/copy_ref.hpp"
#include "meta/bits/remove_reference.hpp"

namespace stl {

template <class T, class Source>
struct copy_cvref : copy_ref<
    copy_cv_t<T, remove_reference_t<Source>>,
    Source
> {};

template <class T, class S>
using copy_cvref_t = typename copy_cvref<T, S>::type;

} // namespace stl

#endif // META_BITS_COPY_CVREF
