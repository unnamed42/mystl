#ifndef __RUBBISH_FORWARD_LIST_BASE__
#define __RUBBISH_FORWARD_LIST_BASE__

#include <stdexcept>
#include <initializer_list> // std::initializer_list
#include <bits/move.h> // std::move
#include "../iterator.hpp"

namespace rubbish{
    
    namespace helper{
        template <class T> struct forward_list_node{
            typedef forward_list_node<T> self_type;
            
            T data;
            self_type *next;
            
            constexpr forward_list_node():data(T()),next(nullptr) {}
            explicit forward_list_node(const T &elem):data(elem),next(nullptr) {}
            explicit forward_list_node(T &&elem):data(std::move(elem)),next(nullptr) {}
            forward_list_node(const self_type &o):data(o.data),next(nullptr) {}
            forward_list_node(self_type &&o):data(std::move(data)),next(nullptr) {}
            
            self_type& operator=(const self_type &o) {data=o.data;next=o.next;return *this;}
            self_type& operator=(self_type &&o) {data=std::move(o.data);next=o.next;return *this;}
        };
    } // namespace helper
    
    // Minimum requirements of type `Node`:
    //   A data member variable named `data`;
    //   A pointer member variable named `next`;
    //   `Node` can be default-initialized and value-initialized.
    
    template <class T,class Node = rubbish::helper::forward_list_node<T> > class forward_list_base{
        public:
            typedef forward_list_base<T,Node> self_type;
            
            typedef Node node;
            
            class iterator:public rubbish::iterator<std::forward_iterator_tag,T>{
                private:
                    typedef rubbish::iterator<std::forward_iterator_tag,T> base_class;
                public:
                    typedef typename base_class::reference reference;
                    typedef typename base_class::pointer   pointer;
                    
                    typedef iterator                                  self_type;
                    typedef typename forward_list_base<T,Node>::node* data_type;
                    
                    explicit iterator(const data_type &cursor):m_cursor(cursor) {}
                    iterator(const self_type &other):m_cursor(other.m_cursor) {}
                    ~iterator() {}
                    
                    reference operator*() const {return m_cursor->data;}
                    pointer operator->() const {return &operator*();}
                    data_type get() const {return m_cursor;}
                    
                    self_type& operator++() {m_cursor=(m_cursor==nullptr?nullptr:m_cursor->next);return *this;}
                    self_type operator++(int) {auto i=*this;operator++();return i;}
                    
                    bool operator==(const self_type &other) const {return m_cursor==other.m_cursor;}
                    bool operator!=(const self_type &other) const {return !operator==(other);}
                    self_type& operator=(const self_type &other) {m_cursor=other.m_cursor;}
                private:
                    data_type m_cursor;
            };
            
            class reverse_iterator:public rubbish::reverse_iterator<iterator> {
                private:
                    typedef rubbish::reverse_iterator<iterator> base_class;
                public:
                    typedef typename base_class::reference reference;
                    typedef typename base_class::pointer   pointer;
                    
                    using base_class::base_class;
                    
                    reference operator*() const {return *m_iter;}
                    pointer operator->() const {return &operator*();}
                private:
                    using base_class::m_iter;
            };
            
            typedef rubbish::const_iterator<iterator> const_iterator;
            
        protected:
            node *m_head;
            node *m_end;// the actual final node of forward_list_base
            std::size_t m_length;
        public:
            // Default Initialization
            constexpr forward_list_base();
            
            // Initialize a forward_list_base of given length, filled by the given value.
            forward_list_base(std::size_t,const T&);
            
            // Move-constructor
            forward_list_base(self_type&&);
            
            // Copy-constructor
            forward_list_base(const self_type&);
            
            // Construct from the given forward_list_base
            explicit forward_list_base(std::initializer_list<T>&&);
            
            // Destructor
            virtual ~forward_list_base();
            
            // Return the size of this forward_list_base
            std::size_t size() const noexcept;
            
            // Reverse the whole forward_list_base
            void reverse();
            
            // Check emptiness
            bool empty() const;
            
            // Sort this list in ascending order, using merge sort method
            void sort();
            
            // Remove all contents
            void clear();
            
            // Add an element to the end of this list
            void push_back(const T&);
            
            // Remove the element at the end of this list
            // cannot be accomplished by a singly-linked list
            // void pop_back();
            
            // Add an element to the head of this list
            void push_front(const T&);
            
            // Remove the element at the head of this list
            void pop_front();
            
            // Get the element at the front
            T& front() const;
            
            // Get the element at the back
            T& back() const;
            
            // Remove the node after `it`
            void remove_after(iterator);
            
            // Remove elements that equals `elem`
            void remove_elem(const T &elem);
            
            // Insert element after node `it`
            void insert_after(iterator,const T&);
            
            // Search the first element that equals `data`
            iterator search(const T&) const;
            
            // Iterator functions
            iterator begin();
            iterator end();
            const_iterator cbegin() const;
            const_iterator cend() const;
            
            // Assignment operators to remove warning [-Weffc++]
            self_type& operator=(const self_type&);
            self_type& operator=(self_type&&);
    };

} // namespace rubbish

#include "forward_list_base.cc"

#endif // __RUBBISH_FORWARD_LIST_BASE__
