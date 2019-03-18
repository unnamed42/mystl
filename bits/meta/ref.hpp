#ifndef META_REF
#define META_REF

#include "def.hpp"

// meta function for pointers, references, raw arrays

namespace rubbish {

template <class T> struct remove_extent                 { using type = T; };
template <class T> struct remove_extent<T[]>            { using type = T; };
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

template <class T> struct is_reference     : false_type {};
template <class T> struct is_reference<T&> : true_type  {};
template <class T> constexpr inline bool is_reference_v = is_reference<T>::value;

template <class T> struct is_rvalue_reference      : false_type {};
template <class T> struct is_rvalue_reference<T&&> : true_type  {};
template <class T> constexpr inline bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

template <class T> struct is_pointer     : false_type {};
template <class T> struct is_pointer<T*> : true_type  {};
template <class T> constexpr inline bool is_pointer_v = is_pointer<T>::value;

template <class T> struct is_array                 : false_type {};
template <class T, size_t N> struct is_array<T[N]> : true_type  {};
template <class T> constexpr inline bool is_array_v = is_array<T>::value;

} // namespace rubbish

#endif // META_REF
