#ifndef UTILITY_DETAIL_PACK_EXPANSION
#define UTILITY_DETAIL_PACK_EXPANSION

namespace stl {

// helper struct to call function on variadic parameter pack
// using a struct over a function that accepts variadic arguments
// is that a initializer list has guaranteed left-to-right evaluation order
struct pack_expansion {
    template <class ...Args>
    pack_expansion(Args&& ...) {}
};

} // namespace stl

#define CALL_ON_PACK(pattern) \
    stl::pack_expansion{ (static_cast<void>( \
        (pattern) \
    ), 0)... }

#endif // UTILITY_DETAIL_PACK_EXPANSION
