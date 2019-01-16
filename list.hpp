#ifndef __RUBBISH_LIST__
#define __RUBBISH_LIST__

#include "bits/linear/list_base.hpp"

namespace rubbish{
    
    template <class T,class Node = helper::list_node<T> > using list = list_base<T,Node>;
    
} // namespace rubbish

#endif // __RUBBISH_LIST__
