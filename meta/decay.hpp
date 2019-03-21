#ifndef META_DECAY
#define META_DECAY

#include "meta/cv.hpp"
#include "meta/ref.hpp"
#include "meta/condition.hpp"
#include "concept/function.hpp"

namespace stl {

template<class T>
struct decay {
private:
    using U = stl::remove_reference_t<T>;
public:
    using type = stl::condition_t<
        stl::is_array_v<U>,
        stl::remove_extent_t<U>*,
        stl::condition_t<
            stl::function<U>::value,
            stl::add_pointer_t<U>,
            stl::remove_cv_t<U>
        >
    >;
};

template <class T> using decay_t = typename decay<T>::type;

} // namespace stl

#endif // META_DECAY
