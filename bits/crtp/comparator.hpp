#ifndef COMPARABLE
#define COMPARABLE

#include "meta/cv.hpp"
#include "meta/ref.hpp"
#include "meta/check.hpp"
#include "meta/enable_if.hpp"

namespace rubbish {

namespace detail {
template <class>
struct compared_type_impl {};

template <class Class, class Ret, class Comp>
struct compared_type_impl<Ret(Class::*)(Comp)> {
    using type = remove_cv_t<remove_reference_t<Comp>>;
};

///
/// should we support compare as a static member function?
///
// template <class Class, class Ret, class Comp>
// struct compared_type_impl<Ret(*)(Class, Comp)> {
//     using type = remove_cv_t<remove_reference_t<Comp>>;
// };

} // namespace detail

template <class Derived>
class comparable {
private:
    using compared_type = typename detail::compared_type_impl<decltype(&Derived::compare)>::type;

    static       Derived& derived()       noexcept { return *static_cast<Derived*>(this); }
    static const Derived& derived() const noexcept { return *static_cast<const Derived*>(this); }
public:
#define EXPAND_COMPARATOR(op) \
    bool operator op(const compared_type &com) const { return derived().compare(com) op 0; }

    EXPAND_COMPARATOR(==)
    EXPAND_COMPARATOR(!=)
    EXPAND_COMPARATOR(<)
    EXPAND_COMPARATOR(>)
    EXPAND_COMPARATOR(<=)
    EXPAND_COMPARATOR(>=)

#undef EXPAND_COMPARATOR
};

#define EXPAND_FREE_COMPARATOR(op, reverse) \
    template <class Class, class Compared> \
    enable_if_t<!is_same<Compared, Class>::value> operator op (const Compared &com, const Class &obj) { return 0 reverse obj.compare(com); }

#define EXPAND_FREE_COMPARATOR2(op) \
    template <class Class, class Compared> \
    enable_if_t<!is_same<Compared, Class>::value> operator op (const Compared &com, const Class &obj) { return 0 op obj.compare(com); }

    EXPAND_FREE_COMPARATOR(<, >)
    EXPAND_FREE_COMPARATOR(>, <)
    EXPAND_FREE_COMPARATOR(<=, >=)
    EXPAND_FREE_COMPARATOR(>=, <=)
    EXPAND_FREE_COMPARATOR2(==)
    EXPAND_FREE_COMPARATOR2(!=)

#undef EXPAND_FREE_COMPARATOR2
#undef EXPAND_FREE_COMPARATOR

} // namespace rubbish

#endif // COMPARABLE
