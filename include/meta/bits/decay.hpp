#ifndef META_BITS_DECAY
#define META_BITS_DECAY

#include "meta/bits/condition.hpp"
#include "meta/bits/remove_cv.hpp"
#include "meta/bits/remove_extent.hpp"
#include "meta/bits/remove_reference.hpp"
#include "meta/bits/add_pointer.hpp"
#include "meta/bits/is_array.hpp"
#include "meta/bits/is_function.hpp"

namespace stl {

template<class T>
struct decay {
private:
    using U = remove_reference_t<T>;
public:
    using type = condition_t<
        is_array_v<U>,
        remove_extent_t<U>*,
        condition_t<
            is_function_v<U>,
            add_pointer_t<U>,
            remove_cv_t<U>
        >
    >;
};

template <class T> using decay_t = typename decay<T>::type;

} // namespace stl

#endif // META_BITS_DECAY
