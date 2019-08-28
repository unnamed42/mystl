#ifndef META_IS_REFERENCE_WRAPPER
#define META_IS_REFERENCE_WRAPPER

#include "meta/base/constant.hpp"

namespace stl {

namespace utility {
template <class> class reference_wrapper;
}

namespace meta {

template <class>
struct is_reference_wrapper : false_type {};

template <class T>
struct is_reference_wrapper<utility::reference_wrapper<T>> : true_type {};

}

} // namespace stl

#endif // META_IS_REFERENCE_WRAPPER
