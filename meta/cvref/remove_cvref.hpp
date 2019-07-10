#ifndef META_REMOVE_CVREF
#define META_REMOVE_CVREF

#include "meta/base/type.hpp"

namespace stl::meta {

template <class T> struct remove_const          : type<T> {};
template <class T> struct remove_const<const T> : type<T> {};
template <class T> using  remove_const_t = typename remove_const<T>::type;

template <class T> struct remove_volatile             : type<T> {};
template <class T> struct remove_volatile<volatile T> : type<T> {};
template <class T> using  remove_volatile_t = typename remove_volatile<T>::type;

template <class T> struct remove_cv : remove_volatile<remove_const_t<T>> {};
template <class T> using  remove_cv_t = typename remove_cv<T>::type;

template <class T> struct remove_pointer                    : type<T> {};
template <class T> struct remove_pointer<T*>                : type<T> {};
template <class T> struct remove_pointer<T* const>          : type<T> {};
template <class T> struct remove_pointer<T* volatile>       : type<T> {};
template <class T> struct remove_pointer<T* const volatile> : type<T> {};
template <class T> using  remove_pointer_t = typename remove_pointer<T>::type;

template <class T> struct remove_reference      : type<T> {};
template <class T> struct remove_reference<T&>  : type<T> {};
template <class T> struct remove_reference<T&&> : type<T> {};
template <class T> using  remove_reference_t = typename remove_reference<T>::type;

template <class T> struct remove_extent                 : type<T> {};
template <class T> struct remove_extent<T[]>            : type<T> {};
template <class T, size_t N> struct remove_extent<T[N]> : type<T> {};
template <class T> using  remove_extent_t = typename remove_extent<T>::type;

template <class T> struct remove_cvref : remove_cv<remove_reference_t<T>> {};
template <class T> using  remove_cvref_t = typename remove_cvref<T>::type;

} // namespace stl::meta

#endif // META_REMOVE_CVREF
