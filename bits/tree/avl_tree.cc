// Algorithms are borrowed from http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
// and http://www.geeksforgeeks.org/avl-tree-set-2-deletion/

namespace rubbish{
    namespace helper{
        // helper function
        // T1, T2 and T3 are subtrees of the tree rooted with y (on left side) 
        // or x (on right side)
        //              y                          x
        //             / \     Right Rotation     /  \ 
        //            x   T3   – – – – – – – >   T1   y 
        //           / \       < - - - - - - -       / \ 
        //          T1  T2     Left Rotation       T2  T3
        
        template <class Node> Node* avl_left_rotate(Node *root){
            auto x=root->right,y=x->left;
            
            // Rotation
            x->left = root;
            root->right = y;
            
            // Update height
            root->height = max(avl_height<Node>(root->left),avl_height<Node>(root->right))+1;
            x->height = max(avl_height<Node>(x->left),avl_height<Node>(x->right))+1;
            
            // Fix `parent`
            if(y!=nullptr)
                y->parent=root;
            if(x!=nullptr)
                x->parent=root->parent;
            root->parent=x;
            
            // Return new tree root
            return x;
        }

        template <class Node> Node* avl_right_rotate(Node *root){
            auto x=root->left,y=x->right;
            
            // Rotation
            x->right = root;
            root->left = y;
            
            // Update height
            root->height = max(avl_height<Node>(root->left),avl_height<Node>(root->right))+1;
            x->height = max(avl_height<Node>(x->left), avl_height<Node>(x->right))+1;
            
            // Fix `parent`
            if(y!=nullptr)
                y->parent=root;
            if(x!=nullptr)
                x->parent=root->parent;
            root->parent=x;
            
            // Return new root
            return x;
        }
        
    } // namespace helper
} // namespace rubbish

template <class T,class Node> template <class U> typename rubbish::avl_tree<T,Node>::node* rubbish::avl_tree<T,Node>::insert(node *root,U &&value,node* &return_val){
    // Perform the normal BST rotation
    if(root==nullptr){
        return_val=root=new node(std::forward<U>(value));
        return root;
    }
    
    if (std::forward<U>(value) < root->data){
        root->left=insert(root->left, std::forward<U>(value),return_val);
        root->left->parent=root;
    }
    else if(std::forward<U>(value) == root->data){
        return_val = root;
        return root;
    } else{
        root->right=insert(root->right, std::forward<U>(value),return_val);
        root->right->parent=root;
    }
    
    auto &&_value = return_val->data;
    
    // Update root height
    root->height = helper::max(helper::avl_height<Node>(root->left), helper::avl_height<Node>(root->right)) + 1;
    
    // Get balance factor of root
    auto factor = helper::avl_balance<Node>(root);
    
    // When unbalanced, do some rotations
    // 1. Left Left Case
    if (factor > 1 && _value < root->left->data)
        return helper::avl_right_rotate(root);
    
    // 2. Right Right Case
    if (factor < -1 && _value > root->right->data)
        return helper::avl_left_rotate(root);
    
    // 3. Left Right Case
    if (factor > 1 && _value > root->left->data){
        root->left=helper::avl_left_rotate(root->left);
        return helper::avl_right_rotate(root);
    }
    
    // 4. Right Left Case
    if (factor < -1 && _value < root->right->data){
        root->right=helper::avl_right_rotate(root->right);
        return helper::avl_left_rotate(root);
    }
    
    // 5. A balanced root, do nothing
    return root;
}

template <class T,class Node> template <class U> typename rubbish::avl_tree<T,Node>::node* rubbish::avl_tree<T,Node>::erase(node* root,U &&value){
    // PERFORM STANDARD BST DELETE
    if (root == nullptr)
        return nullptr;
    
    // If the value to be deleted is smaller than the root's value,
    // then it lies in left subtree
    if ( value < root->data )
        root->left=erase(root->left, std::forward<U>(value));
    
    // If the value to be deleted is greater than the root's value,
    // then it lies in right subtree
    else if( value > root->data )
        root->right=erase(root->right, std::forward<U>(value));
    
    // if value is same as root's value, then This is the node
    // to be deleted
    else{
        // node with only one child or no child
        if( (root->left == nullptr) || (root->right == nullptr) ){
             auto temp = root->left!=nullptr ? root->left : root->right;

            // No child case
            if(temp == nullptr){
                temp = root;
                root = nullptr;
            } else{
                 // One child case, copy the contents of the non-empty child
                root->data=std::move(temp->data);
                root->height=temp->height;
                root->left=temp->left;
                root->right=temp->right;
                if(temp->left!=nullptr)
                    temp->left->parent=root;
                if(temp->right!=nullptr)
                    temp->right->parent=root;
            }
            delete temp;
        } else {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            auto temp = min_node(root->right);
            
            // Copy the inorder successor's data to this node
            root->data = temp->data;
            
            // Delete the inorder successor
            root->right=erase(root->right, temp->data);
        }
    }
    
    // If the tree had only one node then return
    if (root == nullptr)
      return root;
    
    // UPDATE HEIGHT OF THE CURRENT NODE
    root->height = helper::max(helper::avl_height<Node>(root->left), helper::avl_height<Node>(root->right)) + 1;
    
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    auto factor = helper::avl_balance<Node>(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (factor > 1 && helper::avl_balance<Node>(root->left) >= 0)
        return helper::avl_right_rotate(root);;
 
    // Left Right Case
    if (factor > 1 && helper::avl_balance<Node>(root->left) < 0){
        root->left=helper::avl_left_rotate(root->left);
        return helper::avl_right_rotate(root);
    }
 
    // Right Right Case
    if (factor < -1 && helper::avl_balance<Node>(root->right) <= 0)
        return helper::avl_left_rotate(root);
 
    // Right Left Case
    if (factor < -1 && helper::avl_balance<Node>(root->right) > 0){
        root->right = helper::avl_right_rotate(root->right);
        return helper::avl_left_rotate(root);
    }
    
    return root;
}

template <class T,class Node> constexpr rubbish::avl_tree<T,Node>::avl_tree():base_class() {}

template <class T,class Node> rubbish::avl_tree<T,Node>::avl_tree(std::initializer_list<T> &&l):base_class() {
    node *dummy;
    for(auto &&i:l)
        m_root=insert(m_root,std::move(i),dummy);
}

template <class T,class Node> rubbish::avl_tree<T,Node>::avl_tree(const self_type &other):base_class(other) {}

template <class T,class Node> rubbish::avl_tree<T,Node>::avl_tree(self_type &&other):base_class(std::move(other)) {}

template <class T,class Node> template <class U> typename rubbish::avl_tree<T,Node>::const_iterator rubbish::avl_tree<T,Node>::find(U &&value) const {return const_iterator(const_cast<self_type*>(this)->find(std::move(value)));}

template <class T,class Node> template <class U> typename rubbish::avl_tree<T,Node>::iterator rubbish::avl_tree<T,Node>::find(U &&value){
    node *ptr=m_root;
    while(ptr!=nullptr){
        if(value==ptr->data)
            break;
        else if(value<ptr->data)
            ptr=ptr->left;
        else
            ptr=ptr->right;
    }
    return iterator(ptr);
}

template <class T,class Node> template <class U> typename rubbish::avl_tree<T,Node>::iterator rubbish::avl_tree<T,Node>::insert(U &&value) {
    node *inserted=nullptr;
    m_root=insert(m_root,std::forward<U>(value),inserted);
    return iterator(inserted);
}

template <class T,class Node> template <class U> void rubbish::avl_tree<T,Node>::erase(U &&value) { m_root=erase(m_root,std::forward<U>(value)); }

template <class T,class Node> typename rubbish::avl_tree<T,Node>::self_type& rubbish::avl_tree<T,Node>::operator=(const self_type &o) {
    this->~avl_tree();
    m_root=nullptr;
    base_class::copy_subtree(m_root,o.m_root);
    return *this;
}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::self_type& rubbish::avl_tree<T,Node>::operator=(self_type &&o) {
    this->~avl_tree();
    m_root=o.m_root;
    o.m_root=nullptr;
    return *this;
}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::iterator rubbish::avl_tree<T,Node>::begin() { return base_class::inorder_begin();}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::iterator rubbish::avl_tree<T,Node>::end() { return base_class::inorder_end();}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::const_iterator rubbish::avl_tree<T,Node>::cbegin() const { return base_class::inorder_cbegin();}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::const_iterator rubbish::avl_tree<T,Node>::cend() const { return base_class::inorder_cend();}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::reverse_iterator rubbish::avl_tree<T,Node>::rbegin() { return base_class::inorder_rbegin();}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::reverse_iterator rubbish::avl_tree<T,Node>::rend() { return base_class::inorder_rend();}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::const_reverse_iterator rubbish::avl_tree<T,Node>::crbegin() const { return base_class::inorder_crbegin();}

template <class T,class Node> typename rubbish::avl_tree<T,Node>::const_reverse_iterator rubbish::avl_tree<T,Node>::crend() const { return base_class::inorder_crend();}
