#ifndef META_BITS_SEQUENCE
#define META_BITS_SEQUENCE

namespace stl {

template <class T, T...> struct sequence {
    using type = sequence;
};

template <class...> struct types {
    using type = types;
};

} // namespace stl

#endif // META_BITS_SEQUENCE
