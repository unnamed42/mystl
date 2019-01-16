#ifndef __RUBBISH_WRAPPER__
#define __RUBBISH_WRAPPER__

#include "../type_traits/basic_traits.hpp"
#include "../type_traits/remove_qualifier.hpp"

// Only normal and const member functions can be detected.
#define HAS_DETECTOR(func_name)\
template <class T,class ReturnType,class ...Args> struct has_##func_name{\
    private:\
        typedef char yes;\
        typedef struct{char c[2];} no;\
    public:\
        template <class U,ReturnType (U::*)(Args...)> struct sfinae;\
        template <class U,ReturnType (U::*)(Args...) const> struct sfinae_const;\
        template <class U> static yes test(sfinae<U,&U::func_name>*);\
        template <class U> static yes test(sfinae_const<U,&U::func_name>*);\
        template <class U> static no test(...);\
        constexpr static bool value = sizeof(test<T>(0))==sizeof(yes);\
}

namespace rubbish{
    
    namespace helper{
        
        HAS_DETECTOR(sort);
        template <class T,bool=has_sort<typename remove_reference<T>::type,void>::value> struct sort_w{
            static void sort(T &obj) { obj.sort(); }
        };
        template <class T> struct sort_w<T,false>{
            static void sort(...) {}
        };
        
        HAS_DETECTOR(empty);
        template <class T,bool=has_empty<typename remove_reference<T>::type,bool>::value> struct empty_w{
            static bool empty(T &obj) {return obj.empty();}
        };
        template <class T> struct empty_w<T,false>{
            static bool empty(T &obj) {return obj==T();}
        };
        
        HAS_DETECTOR(address_of);
        template <class T,bool=has_address_of<T,typename remove_reference<T>::type>::value> struct address_w{
            static typename remove_reference<T>::type* address(T &obj) {return obj.address_of();}
        };
        template <class T> struct address_w<T,false>{
            typedef typename remove_reference<T>::type type;
            static type* address(T &obj) {return reinterpret_cast<type*>(&reinterpret_cast<char&>(obj));}
        };
        
        
    } // namespace helper
    
    template <class T> void sort(T &obj) { helper::sort_w<T>::sort(obj); }
    
    template <class T> bool empty(T &obj) {return helper::empty_w<T>::empty(obj);}
    
} // namespace rubbish

#undef HAS_DETECTOR

#endif // __RUBBISH_WRAPPER__
