#ifndef FUNCTIONAL_RELATION
#define FUNCTIONAL_RELATION

#include "functional/logic.hpp"

namespace stl {

#define DEPLOY_OPERATOR(classname, op) \
    template <class T = void> \
    struct classname { \
        constexpr bool operator()(const T &lhs, const T &rhs) const { \
            return lhs op rhs; \
        } \
    }; \
    template <> struct classname<void> { \
        template <class T> \
        constexpr bool operator()(const T &lhs, const T &rhs) const { \
            return lhs op rhs; \
        } \
    }

DEPLOY_OPERATOR(eq, ==);
DEPLOY_OPERATOR(ne, !=);
DEPLOY_OPERATOR(lt, <);
DEPLOY_OPERATOR(gt, >);
DEPLOY_OPERATOR(le, <=);
DEPLOY_OPERATOR(ge, >=);

#undef DEPLOY_OPERATOR

} // namespace stl

#endif // FUNCTIONAL_RELATION
