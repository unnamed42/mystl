#ifndef __RUBBISH_IS_CHECKERS__
#define __RUBBISH_IS_CHECKERS__

#include "basic_traits.hpp"
#include "remove_qualifier.hpp"

namespace rubbish{
    
    // Forward-declaration
    template <class T> struct is_arithmetic;
    
    namespace helper{
        // This helper is from https://stackoverflow.com/a/2913870
        template <class Base,class Derived> struct is_base_of_h{
            operator Base*() const;
            operator Derived*();
            // Optional: split functions and custom conversion operators in two classes
            template <class T> static yes test(Derived*,T);
            static no test(Base*,int);
        };
        
        struct is_class_h{
            template <class T> static yes test(int T::*);
            template <class T> static no test(...);
        };
        
        template <class T> struct is_pointer_h:public false_type{};
        template <class T> struct is_pointer_h<T*>:public true_type{};
        
        template <class T> struct is_member_pointer_h:public false_type{};
        template <class T,class U> struct is_member_pointer_h<U T::*>:public true_type{};
        
        // A very naive implementation
        template <class T> struct is_integral_h:public false_type {};
        template <> struct is_integral_h<bool>:public true_type {};
        template <> struct is_integral_h<char>:public true_type {};
        template <> struct is_integral_h<signed char>:public true_type {};
        template <> struct is_integral_h<unsigned char>:public true_type {};
        template <> struct is_integral_h<wchar_t>:public true_type {};
        template <> struct is_integral_h<char16_t>:public true_type {};
        template <> struct is_integral_h<char32_t>:public true_type {};
        template <> struct is_integral_h<short>:public true_type {};
        template <> struct is_integral_h<unsigned short>:public true_type {};
        template <> struct is_integral_h<int>:public true_type {};
        template <> struct is_integral_h<unsigned int>:public true_type {};
        template <> struct is_integral_h<long>:public true_type {};
        template <> struct is_integral_h<unsigned long>:public true_type {};
        template <> struct is_integral_h<long long>:public true_type {};
        template <> struct is_integral_h<unsigned long long>:public true_type {};
        
        template <class T> struct is_floating_point_h:public false_type {};
        template <> struct is_floating_point_h<float>:public true_type {};
        template <> struct is_floating_point_h<double>:public true_type {};
        template <> struct is_floating_point_h<long double>:public true_type {};
        
        template <class T,bool = is_arithmetic<T>::value> struct is_signed_h:public constant<bool,(T(0)>T(-1))> {};
        template <class T> struct is_signed_h<T,false>:public false_type {};
        
        template <class T,bool = is_arithmetic<T>::value> struct is_unsigned_h:public constant<bool,(T(0)<T(-1))> {};
        template <class T> struct is_unsigned_h<T,false>:public false_type {};
        
        template <class T> struct is_char_h:public false_type {};
        template <> struct is_char_h<char>:public true_type {};
        template <> struct is_char_h<signed char>:public true_type {};
        template <> struct is_char_h<unsigned char>:public true_type {};
        template <> struct is_char_h<wchar_t>:public true_type {};
        template <> struct is_char_h<char16_t>:public true_type {};
        template <> struct is_char_h<char32_t>:public true_type {};
    } // namespace helper
    
    template <class T> struct is_array:public false_type {};
    template <class T> struct is_array<T[]>:public true_type {};
    template <class T, unsigned long long N> struct is_array<T[N]>:public true_type {};
    
    template <class T> struct is_const:public false_type {};
    template <class T> struct is_const<const T>:public true_type {};
    
    template <class T> struct is_volatile:public false_type {};
    template <class T> struct is_volatile<volatile T>:public true_type {};
    
    template <class T> struct is_void:public is_same<void,typename remove_cv<T>::type> {};
    
    template <class T> struct is_integral:public helper::is_integral_h<typename remove_cv<T>::type> {};
    
    template <class T> struct is_floating_point:public helper::is_floating_point_h<typename remove_cv<T>::type> {};
    
    template <class T> struct is_arithmetic:public constant<bool,is_integral<T>::value||is_floating_point<T>::value> {};
    
    template <class T> struct is_signed:public helper::is_signed_h<T> {};
    
    template <class T> struct is_unsigned:public helper::is_unsigned_h<T> {};
    
    template <class T> struct is_char:public helper::is_char_h<typename remove_cv<T>::type> {};
    
    template <class T> struct is_class:public constant<bool,sizeof(helper::is_class_h::test<T>(0))==sizeof(helper::yes)> {};
    
    // `is_base_of` and its helper are from https://stackoverflow.com/a/2913870
    template <class Base,class Derived> struct is_base_of:public constant<bool,sizeof(helper::is_base_of_h<Base,Derived>::test(helper::is_base_of_h<Base,Derived>(),int()))==sizeof(helper::yes)> {};
    
    template <class T> struct is_pointer:public helper::is_pointer_h<typename remove_cv<T>::type> {};
    
    template <class T> struct is_member_pointer:public helper::is_member_pointer_h<typename remove_cv<T>::type> {};
    
    // Check if type T is a function.
    // Types like function, lambdas,classes with overloaded operator() and pointers to functions doesn't count as a function type.
    template <class> struct is_function:public false_type { };
    // Regular functions
    template <class Ret,class ...Args> struct is_function<Ret(Args...) >:public true_type {};
    // Variadic functions
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) >:public true_type {};
    // cv-qualified functions
    template <class Ret,class ...Args> struct is_function<Ret(Args...) const>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) volatile>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) const volatile>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) const>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) volatile>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) const volatile>:public true_type {};
    // ref-qualified, cv-qualified functions
    template <class Ret,class ...Args> struct is_function<Ret(Args...)&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) const&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) volatile&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) const volatile&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...)&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) const&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) volatile&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) const volatile&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...)&&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) const&&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) volatile&&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...) const volatile&&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...)&&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) const&&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) volatile&&>:public true_type {};
    template <class Ret,class ...Args> struct is_function<Ret(Args...,...) const volatile&&>:public true_type {};
    
    
} // namespace rubbish
#endif // __RUBBISH_IS_CHECKERS__
