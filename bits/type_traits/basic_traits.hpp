#ifndef __RUBBISH_BASIC_TRAITS__
#define __RUBBISH_BASIC_TRAITS__

namespace rubbish{
    
    // Base class of all is_xxx
    template <class T,T t> struct constant{
        constexpr static T value = t;
        constexpr operator T() const {return value;}
        constexpr T& operator()() const { return value; }
    };
    typedef constant<bool,true> true_type;
    typedef constant<bool,false> false_type;
    
    template <bool,class True,class False> struct condition {typedef True type;};
    template <class True,class False> struct condition<false,True,False> {typedef False type;};
    
    template <bool,class T = void> struct enable_if {};
    template <class T> struct enable_if<true,T> {typedef T type;};
    
    template <class T,class U> struct is_same:public false_type {};
    template <class T> struct is_same<T,T>:public true_type {};
    
    namespace helper{
        // Just to ensure sizeof(yes)!=sizeof(no)
        typedef char yes;
        typedef struct{char c[2];} no;
    } // namespace helper 
    
} // namespace rubbish

#endif // __RUBBISH_BASIC_TRAITS__
