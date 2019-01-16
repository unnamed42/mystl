#ifndef __RUBBISH_REMOVE_QUALIFIERS__
#define __RUBBISH_REMOVE_QUALIFIERS__

namespace rubbish{
    
    // Remove one dimension of an array type
    template <class T> struct remove_extent {typedef T type;};
    template <class T> struct remove_extent<T[]> {typedef T type;};
    template <class T,unsigned long long N> struct remove_extent<T[N]> {typedef T type;};
    
    template <class T> struct remove_reference { typedef T type; };
    template <class T> struct remove_reference<T&> { typedef T type; };
    template <class T> struct remove_reference<T&&> { typedef T type; };
    
    template <class T> struct remove_pointer { typedef T type; };
    template <class T> struct remove_pointer<T*> { typedef T type; };
    template <class T> struct remove_pointer<T* const> { typedef T type; };
    template <class T> struct remove_pointer<T* const volatile> { typedef T type; };
    
    template <class T> struct remove_const { typedef T type; };
    template <class T> struct remove_const<const T> {typedef T type;};
    
    template <class T> struct remove_volatile { typedef T type; };
    template <class T> struct remove_volatile<volatile T> {typedef T type;};
    
    // Remove the top most cv-qualifiers. Keep in mind that
    // `remove_cv<const volatile int*>::type` is still `const volatile int*`,
    // but `remove_cv<int* const volatile>::type` is `int*`.
    template <class T> struct remove_cv { typedef typename remove_const<typename remove_volatile<T>::type>::type type; };
    
    // Remove reference. This type alias is not a part of std.
    template <class T> using rm_ref = typename remove_reference<T>::type;
    
    // Remove pointer. This type alias is not a part of std.
    template <class T> using rm_ptr = typename remove_pointer<T>::type;
    
    // Remove const qualifiers. This type alias is not a part of std.
    template <class T> using rm_c = typename remove_const<T>::type;
    
    // Remove volatile qualifiers. This type alias is not a part of std.
    template <class T> using rm_v = typename remove_volatile<T>::type;
    
    // Remove cv-qualifiers. This type alias is not a part of std.
    template <class T> using rm_cv = typename remove_cv<T>::type;
    
    // Remove cv-qualifiers and reference. This type alias is not a part of std.
    // Pointer property is not removed.
    template <class T> using raw_type = typename remove_cv<typename remove_reference<T>::type>::type;
    
} // namespace rubbish

#endif // __RUBBISH_REMOVE_QUALIFIERS__
