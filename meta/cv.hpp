#ifndef META_CV
#define META_CV

#include "meta/base.hpp"

namespace stl {

template <class T> struct remove_const          { using type = T; };
template <class T> struct remove_const<const T> { using type = T; };
template <class T> using remove_const_t = typename remove_const<T>::type;

template <class T> struct remove_volatile             { using type = T; };
template <class T> struct remove_volatile<volatile T> { using type = T; };
template <class T> using remove_volatile_t = typename remove_volatile<T>::type;

template <class T> struct remove_cv {
    using type = typename remove_volatile<
                     typename remove_const<T>::type
                 >::type;
};
template <class T> using remove_cv_t = typename remove_cv<T>::type;

template <class T> struct add_const { using type = const T; };
template <class T> using add_const_t = typename add_const<T>::type;

template <class T> struct add_volatile { using type = volatile T; };
template <class T> using add_volatile_t = typename add_volatile<T>::type;

template <class T> struct is_const          : false_type {};
template <class T> struct is_const<const T> : true_type  {};
template <class T> constexpr inline bool is_const_v = is_const<T>::value;

template <class T> struct is_volatile             : false_type {};
template <class T> struct is_volatile<volatile T> : true_type  {};
template <class T> constexpr inline bool is_volatile_v = is_volatile<T>::value;

} // namespace stl

#endif // META_CV
