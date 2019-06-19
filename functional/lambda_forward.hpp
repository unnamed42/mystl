#ifndef FUNCTIONAL_LAMBDA_CAPTURE
#define FUNCTIONAL_LAMBDA_CAPTURE

#include "utility/forward.hpp"
#include "utility/addressof.hpp"

namespace stl {

namespace detail {

template <class T>
struct by_value {
private:
    T t;
public:
    template <class Fwd>
    by_value(Fwd &&fwd) : t(stl::forward<Fwd>(fwd)) {}

    auto&       get() &      { return t; }
    const auto& get() const& { return t; }
    auto        get() &&     { return stl::move(t); }
};

template <class T>
struct by_ref {
private:
    T *p;
public:
    by_ref(T &t) : p(stl::addressof(t)) {}

    auto&       get() &      { return *p; }
    const auto& get() const& { return *p; }
    auto        get() &&     { return stl::move(*p); }
};

template <class T>
struct fwd_capture_wrapper : by_value<T> {
    using by_value<T>::by_value;
};

template <class T>
struct fwd_capture_wrapper<T&> : by_ref<T> {
    using by_ref<T>::by_ref;
};

} // namespace detail

template <class T>
auto fwd_capture(T &&t) {
    return detail::fwd_capture_wrapper<T>{stl::forward<T>(t)};
}

} // namespace mystl

#define CAPTURE_FWD(fwd) \
    stl::fwd_capture(stl::forward<decltype(fwd)>(fwd))

#endif // FUNCTIONAL_LAMBDA_CAPTURE
