#ifndef META_CHECK
#define META_CHECK

#include "def.hpp"

#include "meta/base.hpp"
#include "meta/cvref.hpp"

namespace stl {

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
        template <class T>
        static yes_t test(int T::*);

        static no_t  test(...);
    };

    template <bool, class T>
    struct is_empty_impl : T { unsigned long long data; };

    template <class T>
    struct is_empty_impl<false, T> { unsigned long long data; };
} // namespace detail

template <class T, class U> struct is_same       : false_type {};
template <class T>          struct is_same<T, T> : true_type  {};
template <class T, class U> constexpr inline bool is_same_v = is_same<T, U>::value;

template <class T> struct is_void : is_same<remove_cv_t<T>, void> {};
template <class T> constexpr inline bool is_void_v = is_void<T>::value;

template <class Base, class Derived>
struct is_base_of : constant<bool,
    sizeof(detail::is_base_of_impl<Base, Derived>::test(detail::is_base_of_impl<Base, Derived>{}, int{})) == sizeof(detail::yes_t)> {};
template <class B, class D> constexpr inline bool is_base_of_v = is_base_of<B, D>::value;

template <class T>
struct is_class : constant<bool,
    (sizeof(detail::is_class_impl::test(0)) == sizeof(detail::yes_t))> {};
template <class T> constexpr inline bool is_class_v = is_class<T>::value;

template <class T>
struct is_empty : constant<bool,
    (sizeof(detail::is_empty_impl<is_class_v<T>, T>) == sizeof(unsigned long long))
> {};
template <class T> constexpr inline bool is_empty_v = is_empty<T>::value;

template <class T, template <class...> class Template>
struct is_instance_of : false_type {};
template <template <class...> class Template, class ...Args>
struct is_instance_of<Template<Args...>, Template> : true_type {};
template <class T, template <class...> class Template>
constexpr inline bool is_instance_of_v = is_instance_of<T, Template>::value;

template <class T> struct is_reference      : false_type {};
template <class T> struct is_reference<T&>  : true_type  {};
template <class T> struct is_reference<T&&> : true_type  {};
template <class T> constexpr inline bool is_reference_v = is_reference<T>::value;

template <class T> struct is_lvalue_reference     : false_type {};
template <class T> struct is_lvalue_reference<T&> : true_type  {};
template <class T> constexpr inline bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

template <class T> struct is_rvalue_reference      : false_type {};
template <class T> struct is_rvalue_reference<T&&> : true_type  {};
template <class T> constexpr inline bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

template <class T> class reference_wrapper;
template <class T> struct is_reference_wrapper                       : false_type {};
template <class T> struct is_reference_wrapper<reference_wrapper<T>> : true_type {};
template <class T> constexpr inline bool is_reference_wrapper_v = is_reference_wrapper<T>::value;

template <class T> struct is_pointer     : false_type {};
template <class T> struct is_pointer<T*> : true_type  {};
template <class T> constexpr inline bool is_pointer_v = is_pointer<T>::value;

template <class T> struct is_array                      : false_type {};
template <class T, size_t N> struct is_array<T[N]> : true_type  {};
template <class T> constexpr inline bool is_array_v = is_array<T>::value;

template <class T> struct is_const          : false_type {};
template <class T> struct is_const<const T> : true_type  {};
template <class T> constexpr inline bool is_const_v = is_const<T>::value;

template <class T> struct is_volatile             : false_type {};
template <class T> struct is_volatile<volatile T> : true_type  {};
template <class T> constexpr inline bool is_volatile_v = is_volatile<T>::value;

} // namespace stl

#endif // META_CHECK
