#ifndef __RUBBISH_BINARY_TREE__
#define __RUBBISH_BINARY_TREE__

#include "bits/tree/binary_tree_base.hpp"

namespace rubbish{
    // Minimum requirements of type `node`:
    //   Same as requirements of `node` used in `binary_tree_base`.
    
    template <class T,class Node = helper::binary_tree_node<T> > using binary_tree = binary_tree_base<T,Node>;
} // namespace rubbish

#endif // __RUBBISH_BINARY_TREE__
