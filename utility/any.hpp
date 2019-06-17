#ifndef UTILITY_ANY
#define UTILITY_ANY

#include "meta/ref.hpp"

#include "utility/forward.hpp"

namespace stl {

namespace detail {

    template <class> struct type_id_impl { static void id() {} };

    using type_id_type = void(*)();

    template <class T>
    type_id_type type_id() { return &type_id_impl<T>::id; }

} // namespace detail

// TODO: exception inheritance hierarchy
struct bad_any_cast {};

class any {
    template <class T>
    friend T& any_cast(any &);
private:
    struct placeholder {
        virtual ~placeholder() = default;
    };

    template <class T>
    struct actual_data : placeholder {
        T data;

        actual_data(const T &t)
            : data(t) {}
        actual_data(T &&t)
            : data(move(t)) {}
        virtual ~actual_data() = default;
    };
private:
    placeholder *p;
    detail::type_id_type id;
public:
    any()
        : p(nullptr), id(0) {}

    template <class T>
    any(T &&t)
        : p(new actual_data<remove_reference_t<T>>(forward<T>(t))),
          id(detail::type_id<remove_reference_t<T>>()) {}

    ~any() { delete p; }
};

template <class T>
T& any_cast(any &a) {
    if(a.id == detail::type_id<T>()) {
        auto data = static_cast<any::actual_data<T>*>(a.p);
        return data->data;
    } else
        throw bad_any_cast{};
}

} // namespace stl

#endif // UTILITY_ANY
