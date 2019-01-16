#ifndef __RUBBISH_FORWARD_LIST__
#define __RUBBISH_FORWARD_LIST__

#include "bits/linear/forward_list_base.hpp"

namespace rubbish{
    
    template <class T,class Node = helper::forward_list_node<T> > using forward_list = forward_list_base<T,Node>;
    
} // namespace rubbish

#endif // __RUBBISH_FORWARD_LIST__
