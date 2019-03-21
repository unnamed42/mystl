#ifndef CONCEPT_FUNCTION
#define CONCEPT_FUNCTION

#include "meta/base.hpp"

namespace stl {

template <class T> struct function : stl::false_type {};

template <class Ret, class ...Args> struct function<Ret(Args...)>                        : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) const>                  : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) volatile>               : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) const volatile>         : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) &>                      : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) const &>                : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) volatile &>             : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) const volatile &>       : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) &&>                     : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) const &&>               : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) volatile &&>            : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args...) const volatile &&>      : stl::true_type {};

template <class Ret, class ...Args> struct function<Ret(Args..., ...)>                   : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) const>             : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) volatile>          : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) const volatile>    : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) &>                 : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) const &>           : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) volatile &>        : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) const volatile &>  : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) &&>                : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) const &&>          : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) volatile &&>       : stl::true_type {};
template <class Ret, class ...Args> struct function<Ret(Args..., ...) const volatile &&> : stl::true_type {};

} // namespace stl

#endif // CONCEPT_FUNCTION
