#ifndef __RUBBISH_TYPE_UTILITY__
#define __RUBBISH_TYPE_UTILITY__

#include "../type_traits/add_qualifier.hpp"

namespace rubbish{
    
    // Should only be used when unevaluated
    template <class T> typename add_rvalue_reference<T>::type declval();
    
    template <class T> constexpr typename remove_reference<T>::type&& move(T &&t) noexcept {return static_cast<T&&>(t);}
    
    template <class T> constexpr typename remove_reference<T>::type& forward(T &t) noexcept {return static_cast<T&&>(t);}
    template <class T> constexpr typename remove_reference<T>::type&& forward(T &&t) noexcept {return static_cast<T&&>(t);}
    
    template <class ...Args> struct common_type;
    template <class T> struct common_type<T> { typedef typename decay<T>::type type;};
    template <class T, class U> struct common_type<T, U> {typedef typename decay<decltype(true?declval<T>():declval<U>())>::type type;};
    template <class T, class U, class... V> struct common_type<T, U, V...> {typedef typename common_type<typename common_type<T, U>::type, V...>::type type;};
} // namespace rubbish

#endif // __RUBBISH_TYPE_UTILITY__
