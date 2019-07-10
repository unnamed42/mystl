#ifndef META_COPY_CVREF
#define META_COPY_CVREF

#include "meta/base/type.hpp"
#include "meta/cvref/add_cvref.hpp"

namespace stl::meta {

// copy const/volatile-ness from type S to type T
template <class T, class S> struct copy_cv                      : type<T> {};
template <class T, class S> struct copy_cv<T, const S>          : type<const T> {};
template <class T, class S> struct copy_cv<T, volatile S>       : type<volatile T> {};
template <class T, class S> struct copy_cv<T, const volatile S> : type<const volatile T> {};
template <class T, class S> using  copy_cv_t = typename copy_cv<T, S>::type;

// copy reference-ness from type S to type T
template <class T, class S> struct copy_ref         : type<T> {};
template <class T, class S> struct copy_ref<T, S&>  : add_lvalue_reference<T> {};
template <class T, class S> struct copy_ref<T, S&&> : add_rvalue_reference<T> {};
template <class T, class S> using  copy_ref_t = typename copy_ref<T, S>::type;

template <class T, class Source>
struct copy_cvref : copy_ref<
    copy_cv_t<T, remove_ref_t<Source>>,
    Source
> {};

template <class T, class S>
using copy_cvref_t = typename copy_cvref<T, S>::type;

} // namespace stl::meta

#endif // META_COPY_CVREF
