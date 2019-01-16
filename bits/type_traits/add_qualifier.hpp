#ifndef __RUBBISH_ADD_QUALIFIER__
#define __RUBBISH_ADD_QUALIFIER__

#include "basic_traits.hpp"
#include "is_checkers.hpp"
#include "remove_qualifier.hpp"

namespace rubbish{
    
    namespace helper{
        template <class T,bool function_type=false> struct add_pointer_h {typedef typename remove_reference<T>::type type;};
        template <class T> struct add_pointer_h<T,true> {typedef T type;};
        template < class T,class ...Args> struct add_pointer_h<T(Args...),true> {using type = T(*)(Args...);};
        template < class T,class ...Args> struct add_pointer_h<T(Args...,...),true> {using type = T(*)(Args...,...);};
    } // namespace helper
    
    template <class T> struct add_const {typedef const T type;};
    
    template <class T> struct add_volatile {typedef volatile T type;};
    
    template <class T> struct add_cv {typedef typename add_const<typename add_volatile<T>::type>::type type;};
    
    // Always set `type` as an lvalue reference
    template <class T> struct add_lvalue_reference {typedef T& type;};
    template <class T> struct add_lvalue_reference<T&> {typedef T& type;};
    template <class T> struct add_lvalue_reference<T&&> {typedef T& type;};
    
    // Always set `type` as an rvalue reference
    template <class T> struct add_rvalue_reference {typedef T&& type;};
    template <class T> struct add_rvalue_reference<T&> {typedef T&& type;};
    template <class T> struct add_rvalue_reference<T&&> {typedef T&& type;};
    
    template <class T> struct add_pointer:public helper::add_pointer_h<T,is_function<T>::value> {};
    
    template <class T> struct decay {
        private:
            typedef typename remove_reference<T>::type U;
        public:
            typedef typename condition<is_array<U>::value,
                typename remove_extent<U>::type*,
                typename condition<is_function<U>::value,
                    typename add_pointer<U>::type,
                    typename remove_cv<U>::type
                >::type
            >::type type;
    };
}
#endif // __RUBBISH_ADD_QUALIFIER__
