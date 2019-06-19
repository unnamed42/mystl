#ifndef UTILITY_REFERENCE_WRAPPER
#define UTILITY_REFERENCE_WRAPPER

#include "meta/bits/enable_if.hpp"
#include "meta/bits/remove_cvref.hpp"
#include "meta/bits/declval.hpp"

#include "utility/forward.hpp"
#include "utility/addressof.hpp"

#include "functional/invoke.hpp"

namespace stl {

namespace detail {

    template <class T> T& fun(T &t) noexcept { return t; }
    template <class T> void fun(T&&) = delete;

} // namespace detail

template <class T>
class reference_wrapper {
    T *p;
public:
    using type = T;

    // constructor, copy
    template <class U, class = decltype(
        detail::fun<T>(declval<U>()),
        enable_if_t< !is_same_v<reference_wrapper, remove_cvref_t<U>> >{}
    )>
    reference_wrapper(U &&u) noexcept(noexcept(detail::fun<T>(forward<U>(u))))
        : p(addressof(detail::fun<T>(forward<U>(u)))) {}

    reference_wrapper(const reference_wrapper &) noexcept = default;
    reference_wrapper& operator=(const reference_wrapper&) noexcept = default;

    operator T&()     const noexcept { return *p; }
             T& get() const noexcept { return *p; }

    template <class ...Args>
    void operator()(Args&& ...args) const {
        return invoke(get(), forward<Args>(args)...);
    }
};

} // namespace stl

#endif // UTILITY_REFERENCE_WRAPPER
