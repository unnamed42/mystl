#ifndef META_DECAY
#define META_DECAY

#include "meta/cvref.hpp"
#include "meta/condition.hpp"

#include "concept/function.hpp"

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
            function<U>::value,
            add_pointer_t<U>,
            remove_cv_t<U>
        >
    >;
};

template <class T> using decay_t = typename decay<T>::type;

} // namespace stl

#endif // META_DECAY
