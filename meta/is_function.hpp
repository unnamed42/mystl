#ifndef META_IS_FUNCTION
#define META_IS_FUNCTION

#include "meta/base.hpp"

namespace rubbish {

template <class T> struct is_function : false_type {};

template <class Ret, class ...Args> struct is_function<Ret(Args...)>                        : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) const>                  : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) volatile>               : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) const volatile>         : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) &>                      : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) const &>                : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) volatile &>             : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) const volatile &>       : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) &&>                     : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) const &&>               : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) volatile &&>            : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args...) const volatile &&>      : true_type {};

template <class Ret, class ...Args> struct is_function<Ret(Args..., ...)>                   : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) const>             : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) volatile>          : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) const volatile>    : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) &>                 : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) const &>           : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) volatile &>        : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) const volatile &>  : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) &&>                : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) const &&>          : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) volatile &&>       : true_type {};
template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) const volatile &&> : true_type {};

template <class T> constexpr inline bool is_function_v = is_function<T>::value;

} // namespace rubbish

#endif // META_IS_FUNCTION
