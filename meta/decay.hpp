#ifndef META_DECAY
#define META_DECAY

#include "meta/cv.hpp"
#include "meta/ref.hpp"
#include "meta/condition.hpp"
#include "meta/is_function.hpp"

namespace rubbish {

template<class T>
struct decay {
private:
    using U = remove_reference_t<T>;
public:
    using type = condition_t<
        is_array_v<U>
        remove_extent_t<U>*,
        condition_t<
            is_function_v<U>,
            add_pointer_t<U>,
            remove_cv_t<U>
        >
    >;
};

template <class T> using decay_t = typename decay<T>::type;

} // namespace rubbish

#endif // META_DECAY
