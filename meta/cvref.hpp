#ifndef META_CVREF
#define META_CVREF

#include "def.hpp"

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

template <class T> struct remove_extent                      { using type = T; };
template <class T> struct remove_extent<T[]>                 { using type = T; };
template <class T, size_t N> struct remove_extent<T[N]> { using type = T; };
template <class T> using  remove_extent_t = typename remove_extent<T>::type;

template <class T> struct remove_reference      { using type = T; };
template <class T> struct remove_reference<T&>  { using type = T; };
template <class T> struct remove_reference<T&&> { using type = T; };
template <class T> using  remove_reference_t = typename remove_reference<T>::type;

template <class T> struct remove_pointer                    { using type = T; };
template <class T> struct remove_pointer<T*>                { using type = T; };
template <class T> struct remove_pointer<T* const>          { using type = T; };
template <class T> struct remove_pointer<T* volatile>       { using type = T; };
template <class T> struct remove_pointer<T* const volatile> { using type = T; };
template <class T> using  remove_pointer_t = typename remove_pointer<T>::type;

template <class T> struct add_pointer { using type = T*; };
template <class T> using  add_pointer_t = typename add_pointer<T>::type;

template <class T> struct add_reference { using type = T&; };
template <class T> using  add_reference_t = typename add_reference<T>::type;

template <class T> struct add_rvalue_reference      { using type = T&&; };
template <class T> struct add_rvalue_reference<T&>  { using type = T&; };
template <class T> struct add_rvalue_reference<T&&> { using type = T&&; };
template <class T> using  add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

template <class T> struct remove_cvref { using type = remove_cv_t<remove_ref_t<T>>; };
template <class T> using  remove_cvref_t = typename remove_cvref<T>::type;

} // namespace stl

#endif // META_CVREF
