#ifndef META_VOID_T
#define META_VOID_T

namespace rubbish {

template <class...> struct make_void { using type = void; };

template <class ...Args> using void_t = typename make_void<Args...>::type;

} // namespace rubbish

#endif // META_VOID_T
