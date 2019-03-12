#ifndef META_CHECK
#define META_CHECK

#include "def.hpp"
#include "meta/base.hpp"
#include "meta/cv.hpp"

namespace rubbish {

    namespace detail {
        using yes_t = char[1];
        using no_t  = char[2];

        static_assert(sizeof(yes_t) != sizeof(no_t),
                      "yes_t and no_t requires a different size");

        // from https://stackoverflow.com/a/2913870
        template <class B, class D>
        struct is_base_of_impl {
            operator B*() const;
            operator D*();

            template <class T>
            static yes_t test(D*, T);

            static no_t  test(B*, int);
        };

        struct is_class_impl {
            template <class T> static yes_t test(int T::*);
            template <class T> static no_t  test(...);
        };
    } // namespace detail


template <class T, class U> struct is_same       : false_type {};
template <class T>          struct is_same<T, T> : true_type  {};

template <class T> struct is_void : is_same<remove_cv_t<T>, void> {};

template <class Base, class Derived>
struct is_base_of : constant<bool,
    sizeof(detail::is_base_of_impl<Base, Derived>::test(detail::detail::is_base_of_impl<Base, Derived>{}, int{})) == sizeof(detail::yes_t)> {};

template <class T>
struct is_class : constant<bool,
    sizeof(detail::is_class_impl::test(0) == sizeof(detail::yes_t))> {};

template <class T> struct is_function : false_type {};
#define IS_FUNCTION_NORMAL(variant) \
    template <class Ret, class ...Args> struct is_function<Ret(Args...) variant> : true_type {}
#define IS_FUNCTION_VAARGS(variant) \
    template <class Ret, class ...Args> struct is_function<Ret(Args..., ...) variant> : true_type {}

    IS_FUNCTION_NORMAL();
    IS_FUNCTION_NORMAL(const);
    IS_FUNCTION_NORMAL(volatile);
    IS_FUNCTION_NORMAL(const volatile);
    IS_FUNCTION_NORMAL(&);
    IS_FUNCTION_NORMAL(const &);
    IS_FUNCTION_NORMAL(volatile &);
    IS_FUNCTION_NORMAL(const volatile &);
    IS_FUNCTION_NORMAL(&&);
    IS_FUNCTION_NORMAL(const &&);
    IS_FUNCTION_NORMAL(volatile &&);
    IS_FUNCTION_NORMAL(const volatile &&);
    IS_FUNCTION_VAARGS();
    IS_FUNCTION_VAARGS(const);
    IS_FUNCTION_VAARGS(volatile);
    IS_FUNCTION_VAARGS(const volatile);
    IS_FUNCTION_VAARGS(&);
    IS_FUNCTION_VAARGS(const &);
    IS_FUNCTION_VAARGS(volatile &);
    IS_FUNCTION_VAARGS(const volatile &);
    IS_FUNCTION_VAARGS(&&);
    IS_FUNCTION_VAARGS(const &&);
    IS_FUNCTION_VAARGS(volatile &&);
    IS_FUNCTION_VAARGS(const volatile &&);

#undef IS_FUNCTION_VAARGS
#undef IS_FUNCTION_NORMAL

} // namespace rubbish

#endif // META_CHECK
