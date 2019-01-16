#ifndef __RUBBISH_TRIE_BASE__
#define __RUBBISH_TRIE_BASE__

#include "map.hpp"
#include "type_traits/is_checkers.hpp" // type checks
#include "../utility/pair.hpp"
#include <bits/move.h> // std::move

#define NULL_TERMINATOR '\0'

namespace rubbish{
    
    namespace helper{
        
        template <class Char,bool=is_char<Char>::value> struct trie_node{
            map<Char,trie_node<Char>*> children;
            
            trie_node():children() {}
            explicit trie_node(const Char &d):children({{d,nullptr}}) {}
            trie_node(const trie_node<Char> &other):children(other.children) {}
            trie_node(trie_node<Char> &&other):children(std::move(other.children)) {}
        };
        template <class T> struct trie_node<T,false> {};
        
    } // namespace helper
    
    // Minimum requirements of type `Node`:
    //   A data member variable named `data`;
    //   A container named `children` that supports insert and find;
    //   `Node` can be default-initialized and value-initialized;
    //   `Node` is copy-constructible and move-constructible;
    //   Some more requirements of avl_tree_node's `data` member variable.
    
    // In instantiation, only parameter `Char` of character types are expected.
    template <class Char,class Node = helper::trie_node<Char>,bool = is_char<Char>::value> class trie_tree_base{
        public:
            typedef Node node;
        protected:
            // Delete trie tree rooted with this node
            static void delete_subtree(const node*);
            
        public:
            explicit trie_tree_base(const Char* =nullptr);
            
            virtual ~trie_tree_base();
            
            void insert(const Char*);
            
            // Check if this tree contains the given string, 
            // will return `true` if string pointer is `nullptr` or is an empty string.
            // But an empty tree contains nothing, even the empty string.
            bool has_str(const Char*) const;
            
        protected:
            node* m_root;
    };
    // Other types are invalid.
    template <class Char,class Node> class trie_tree_base<Char,Node,false> {};
    
    
    typedef trie_tree_base<char> trie_tree;
    
} // namespace rubbish

template <class Char,class Node,bool is_char> void rubbish::trie_tree_base<Char,Node,is_char>::delete_subtree(const node *root){
    if(root==nullptr)
        return;
    auto &&children=root->children;
    for(auto it=children.cbegin();it!=children.cbegin();++it)
        delete_subtree(it->second);
    delete root;
}

template <class Char,class Node,bool is_char> rubbish::trie_tree_base<Char,Node,is_char>::trie_tree_base(const Char *str):m_root(nullptr) {insert(str);}

template <class Char,class Node,bool is_char> rubbish::trie_tree_base<Char,Node,is_char>::~trie_tree_base() {delete_subtree(m_root);}

template <class Char,class Node,bool is_char> void rubbish::trie_tree_base<Char,Node,is_char>::insert(const Char *str){
    if(str==nullptr||*str==NULL_TERMINATOR)
        return;
    auto trie_node=&m_root;
    while(*str!=NULL_TERMINATOR){
        if(*trie_node==nullptr)
            *trie_node=new node(*str);
        else{
            auto &&tmp=(*trie_node)->children.insert({*str,nullptr});
            trie_node=&(tmp->second);
        }
        ++str;
    }
}

template <class Char,class Node,bool is_char> bool rubbish::trie_tree_base<Char,Node,is_char>::has_str(const Char *str) const {
    if(m_root==nullptr)
        return false;
    if(str==nullptr)
        return true;
    auto trie_node=m_root;
    while(*str!=NULL_TERMINATOR){
        if(trie_node==nullptr)
            return false;
        auto &&children=trie_node->children;
        auto &&tmp=children.find(*str);
        if(tmp==children.end())
            return false;
        trie_node=tmp->second;
        ++str;
    }
    return true;
}

#include "trie_tree_base.cc"

#undef NULL_TERMINATOR

#endif // __RUBBISH_TRIE_BASE__
