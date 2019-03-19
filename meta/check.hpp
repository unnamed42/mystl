#ifndef META_CHECK
#define META_CHECK

#include "def.hpp"
#include "meta/base.hpp"
#include "meta/cv.hpp"

#include "meta/is_function.hpp"

namespace rubbish {

namespace detail {
    // from https://stackoverflow.com/a/2913870
    template <class B, class D>
    struct is_base_of_impl {
        operator B*() const;
        operator D*();

        template <class T>
        static yes_t test(D*, T);

        static no_t  test(B*, int);
    };

    struct is_class_impl {
        template <class T> static yes_t test(int T::*);
        template <class T> static no_t  test(...);
    };
} // namespace detail

template <class T, class U> struct is_same       : false_type {};
template <class T>          struct is_same<T, T> : true_type  {};
template <class T, class U> constexpr inline bool is_same_v = is_same<T, U>::value;

template <class T> struct is_void : is_same<remove_cv_t<T>, void> {};
template <class T> constexpr inline bool is_void_v = is_void<T>::value;

template <class Base, class Derived>
struct is_base_of : constant<bool,
    sizeof(detail::is_base_of_impl<Base, Derived>::test(detail::detail::is_base_of_impl<Base, Derived>{}, int{})) == sizeof(detail::yes_t)> {};
template <class B, class D> constexpr inline bool is_base_of_v = is_base_of<B, D>::value;

template <class T>
struct is_class : constant<bool,
    sizeof(detail::is_class_impl::test(0) == sizeof(detail::yes_t))> {};
template <class T> constexpr inline bool is_class_v = is_class<T>::value;

template <class T, template <class...> class Template>
struct is_instance_of : false_type {};
template <template <class...> class Template, class ...Args>
struct is_instance_of<Template<Args...>, Template> : true_type {};
template <class T, template <class...> class Template>
constexpr inline bool is_instance_of_v = is_instance_of<T, Template>::value;

} // namespace rubbish

#endif // META_CHECK
