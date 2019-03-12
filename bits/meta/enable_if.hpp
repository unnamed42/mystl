#ifndef META_ENABLE_IF
#define META_ENABLE_IF

#include "meta/base.hpp"

namespace rubbish {

template <bool B, class T = void>
struct enable_if {  };

template <class T>
struct enable_if<true, T> { using type = T; }

template <bool B, class T>
using enable_if_t = typename enable_if<B, T>::type;

} // namespace rubbish

#endif // META_ENABLE_IF
