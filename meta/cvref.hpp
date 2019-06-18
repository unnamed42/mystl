#ifndef META_CVREF
#define META_CVREF

#include "def.hpp"

#include "meta/base.hpp"

namespace stl {

template <class T> struct remove_const          : identity<T> {};
template <class T> struct remove_const<const T> : identity<T> {};
template <class T> using  remove_const_t = typename remove_const<T>::type;

template <class T> struct remove_volatile             : identity<T> {};
template <class T> struct remove_volatile<volatile T> : identity<T> {};
template <class T> using  remove_volatile_t = typename remove_volatile<T>::type;

template <class T> struct remove_cv : remove_volatile<remove_const_t<T>> {};
template <class T> using  remove_cv_t = typename remove_cv<T>::type;

template <class T> struct remove_extent                 : identity<T> {};
template <class T> struct remove_extent<T[]>            : identity<T> {};
template <class T, size_t N> struct remove_extent<T[N]> : identity<T> {};
template <class T> using  remove_extent_t = typename remove_extent<T>::type;

template <class T> struct remove_reference      : identity<T> {};
template <class T> struct remove_reference<T&>  : identity<T> {};
template <class T> struct remove_reference<T&&> : identity<T> {};
template <class T> using  remove_reference_t = typename remove_reference<T>::type;

template <class T> struct remove_pointer                    : identity<T> {};
template <class T> struct remove_pointer<T*>                : identity<T> {};
template <class T> struct remove_pointer<T* const>          : identity<T> {};
template <class T> struct remove_pointer<T* volatile>       : identity<T> {};
template <class T> struct remove_pointer<T* const volatile> : identity<T> {};
template <class T> using  remove_pointer_t = typename remove_pointer<T>::type;

template <class T> struct remove_cvref : remove_cv<remove_reference_t<T>> {};
template <class T> using  remove_cvref_t = typename remove_cvref<T>::type;

template <class T> struct add_pointer : identity<T*> {};
template <class T> using  add_pointer_t = typename add_pointer<T>::type;

template <class T> struct add_const : identity<const T> {};
template <class T> using  add_const_t = typename add_const<T>::type;

template <class T> struct add_volatile : identity<volatile T> {};
template <class T> using  add_volatile_t = typename add_volatile<T>::type;

template <class T> struct add_cv : add_const<add_volatile_t<T>> {};
template <class T> using  add_cv_t = typename add_cv<T>::type;

template <class T> struct add_reference : identity<T&> {};
template <class T> using  add_reference_t = typename add_reference<T>::type;

template <class T> struct add_rvalue_reference      : identity<T&&> {};
template <class T> struct add_rvalue_reference<T&>  : identity<T&>  {};
template <class T> struct add_rvalue_reference<T&&> : identity<T&&> {};
template <class T> using  add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

} // namespace stl

#endif // META_CVREF
