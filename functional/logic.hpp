#ifndef FUNCTIONAL_LOGIC
#define FUNCTIONAL_LOGIC

#include "utility/bits/forward.hpp"

#include "functional/invoke.hpp"

namespace stl {

template <class Callable>
auto negate(Callable &&call) {
    return [f=forward<Callable>(call)](auto&& ...args) {
        return invoke(forward<Callable>(f), forward<decltype(args)>(args)...);
    };
}

} // namespace stl

#endif // FUNCTIONAL_LOGIC
