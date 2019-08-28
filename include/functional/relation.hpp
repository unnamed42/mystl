#ifndef FUNC_RELATION
#define FUNC_RELATION

namespace stl::func {

#define MYSTL_DEPLOY_OP(name, op) \
    template <class T = void> \
    struct name { \
        constexpr bool operator()(const T &lhs, const T &rhs) const noexcept(noexcept(lhs op rhs)) { \
            return lhs op rhs; \
        } \
    }; \
    template <> struct name<void> { \
        template <class T> \
        constexpr bool operator()(const T &lhs, const T &rhs) const noexcept(noexcept(lhs op rhs)) { \
            return lhs op rhs; \
        } \
    }

MYSTL_DEPLOY_OP(eq, ==);
MYSTL_DEPLOY_OP(ne, !=);
MYSTL_DEPLOY_OP(lt, <);
MYSTL_DEPLOY_OP(gt, >);
MYSTL_DEPLOY_OP(le, <=);
MYSTL_DEPLOY_OP(ge, >=);

#undef MYSTL_DEPLOY_OP

} // namespace stl::func

#endif // FUNC_RELATION
