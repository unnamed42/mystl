#ifndef DEF
#define DEF

namespace stl {

using size_t = decltype(sizeof(0));

using ptrdiff_t = decltype(static_cast<char*>(0) - static_cast<char*>(0));

}

#endif // DEF
