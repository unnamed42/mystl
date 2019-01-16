#ifndef __RUBBISH_LIST_BASE__
#define __RUBBISH_LIST_BASE__

#include <stdexcept>
#include <initializer_list> // std::initializer_list
#include <bits/move.h> // std::move
#include "../iterator.hpp"

namespace rubbish{

    namespace helper{
        template <class T> struct list_node{
            typedef list_node<T> self_type;
            
            T data;
            self_type *prev;
            self_type *next;
            
            list_node():data(),prev(nullptr),next(nullptr) {}
            explicit list_node(const T &elem):data(elem),prev(nullptr),next(nullptr) {}
            explicit list_node(T &&elem):data(std::move(elem)),prev(nullptr),next(nullptr) {}
            list_node(const self_type &o):data(o.data),prev(nullptr),next(nullptr) {}
            list_node(self_type &&o):data(std::move(data)),prev(nullptr),next(nullptr) {}
            
            self_type& operator=(const self_type &o) {data=o.data;next=prev=nullptr;return *this;}
            self_type& operator=(self_type &&o) {data=std::move(o.data);next=prev=nullptr;return *this;}
        };
    } // namespace helper
    
    template <class T,class Node = helper::list_node<T> > class list_base{
        public:
            typedef Node node;
            
            class iterator:public rubbish::iterator<std::bidirectional_iterator_tag,T>{
                private:
                    typedef rubbish::iterator<std::bidirectional_iterator_tag,T> base_class;
                public:
                    typedef typename base_class::reference reference;
                    typedef typename base_class::pointer   pointer;
                    
                    typedef iterator                          self_type;
                    typedef typename list_base<T,Node>::node* data_type;
                    
                    explicit iterator(const data_type &cursor):m_cursor(cursor) {}
                    iterator(const self_type &other):m_cursor(other.m_cursor) {}
                    ~iterator() {}
                    
                    reference operator*() const {return m_cursor->data;}
                    pointer operator->() const {return &operator*();}
                    data_type get() const {return m_cursor;}
                    
                    self_type& operator++() {m_cursor=(m_cursor==nullptr?nullptr:m_cursor->next);return *this;}
                    self_type operator++(int) {auto i=*this;operator++();return i;}
                    self_type& operator--() {m_cursor=(m_cursor==nullptr?nullptr:m_cursor->prev);return *this;}
                    self_type operator--(int) {auto i=*this;operator--();return i;}
                    
                    bool operator==(const self_type &other) const {return m_cursor==other.m_cursor;}
                    bool operator!=(const self_type &other) const {return !operator==(other);}
                    self_type& operator=(const self_type &other) {m_cursor=other.m_cursor;}
                private:
                    data_type m_cursor;
            };
            
            class reverse_iterator:public rubbish::reverse_iterator<iterator>{
                private:
                    typedef rubbish::reverse_iterator<iterator> base_class;
                public:
                    typedef typename base_class::reference reference;
                    typedef typename base_class::pointer   pointer;
                    
                    using base_class::base_class;
                    
                    reference operator*() const {return *m_iter;}
                    pointer operator->() const {return &operator*();}
                protected:
                    using base_class::m_iter;
            };
            
            typedef rubbish::const_iterator<iterator>         const_iterator;
            typedef rubbish::const_iterator<reverse_iterator> const_reverse_iterator;
            
            typedef list_base<T,Node> self_type;
            
        protected:
            node *m_head;
            node *m_end; // actual end of list_base
            std::size_t m_length;
        public:
            // Default initialization
            constexpr list_base();
            
            // Initialize a list_base of given length, filled by the given value.
            list_base(std::size_t,const T&);
            
            // Move-constructor
            list_base(self_type&&);
            
            // Copy-constructor
            list_base(const self_type&);
            
            // Construct from the given list_base
            list_base(std::initializer_list<T>&&);
            
            // Destructor
            virtual ~list_base();
            
            // Return the size of this list_base
            std::size_t size() const noexcept;
            
            // Reverse the whole list_base
            void reverse();
            
            // Check emptiness
            bool empty() const;
            
            // Merge sort in acsending order
            void sort();
            
            // Remove all contents
            void clear();
            
            // Add an element to the end of this list
            void push_back(const T&);
            
            // Remove the element at the end of this list
            void pop_back();
            
            // Add an element to the head of this list
            void push_front(const T&);
            
            // Remove the element at the head of this list
            void pop_front();
            
            // Get the element at the front
            T& front() const;
            
            // Get the element at the back
            T& back() const;
            
            // Remove the node `it`
            void remove(iterator it);
            
            // Iterator functions
            iterator begin();
            iterator end();
            reverse_iterator rbegin();
            reverse_iterator rend();
            const_iterator cbegin() const;
            const_iterator cend() const;
            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;
            
            // Assignment operator to avoid warning [-Weffc++]
            self_type& operator=(const self_type&);
            self_type& operator=(self_type&&);
    };
} // namespace rubbish

#include "list_base.cc"

#endif // __RUBBISH_LIST_BASE__
