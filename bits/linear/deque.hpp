#ifndef __RUBBISH_DEQUE__
#define __RUBBISH_DEQUE__

//#include <cstddef> // included in iterator.hpp
#include <bits/move.h> // std::move
#include "../iterator.hpp"
#include "../utility/pair.hpp"

namespace rubbish{
    
    // Default length of deque's blocks
    constexpr std::size_t __deque_block = 32;
    
    // Default number of deque's blocks
    constexpr std::size_t __deque_base = 2;
    
    template <class T> class deque{
        public:
            class iterator:public rubbish::iterator<std::random_access_iterator_tag,T> {
                private:
                    typedef rubbish::iterator<std::random_access_iterator_tag,T> base_class;
                public:
                    typedef typename base_class::reference       reference;
                    typedef typename base_class::pointer         pointer;
                    typedef typename base_class::difference_type difference_type;
                    
                    typedef iterator self_type;
                    typedef T*       data_type;
                    
                    explicit iterator(const data_type &cursor):m_cursor(cursor) {}
                    iterator(const self_type &o):m_cursor(o.m_cursor) {}
                    ~iterator() {}
                    
                    reference operator*() const {return *m_cursor;}
                    pointer operator->() const {return &operator*();}
                    data_type get() const {return m_cursor;}
                    reference operator[](difference_type n) const {return m_cursor[n];}   
                    
                    self_type& operator++() {++m_cursor;return *this;}
                    self_type operator++(int) {auto i=*this;operator++();return i;}
                    self_type& operator--() {--m_cursor;return *this;}
                    self_type operator--(int) {auto i=*this;operator--();return i;}
                    self_type& operator+=(const difference_type &diff) {m_cursor+=diff;return *this;}
                    self_type operator+(const difference_type &diff) const {return self_type(m_cursor+diff);}
                    self_type& operator-=(const difference_type &diff) {m_cursor-=diff;return *this;}
                    self_type operator-(const difference_type &diff) const {return self_type(m_cursor-diff);}
                    
                    bool operator<(const self_type &o) const {return m_cursor<o.m_cursor;}
                    bool operator>(const self_type &o) const {return m_cursor>o.m_cursor;}
                    bool operator<=(const self_type &o) const {return !operator>(o);}
                    bool operator>=(const self_type &o) const {return !operator<(o);}
                    bool operator==(const self_type &o) const {return m_cursor==o.m_cursor;}
                    bool operator!=(const self_type &o) const {return !operator==(o);}
                    
                    self_type& operator=(const self_type &o) {m_cursor=o.m_cursor;return *this;}
                private:
                    data_type m_cursor;
            };
            
            typedef rubbish::const_iterator<iterator>         const_iterator;
            typedef rubbish::reverse_iterator<iterator>       reverse_iterator;
            typedef rubbish::const_iterator<reverse_iterator> const_reverse_iterator;
            
            typedef deque<T> self_type;
            
        private:
            T **m_map;
            std::size_t m_msize; // map size
            pair<std::size_t,std::size_t> m_start;
            pair<std::size_t,std::size_t> m_end;
        public:
            deque();
            
            deque(const self_type&);
            
            deque(self_type&&);
            
            ~deque();
            
            bool empty() const;
            
            std::size_t size() const;
            
            void push_back(const T&);
            
            void pop_back();
            
            void push_front(const T&);
            
            void pop_front();
            
            T& back();
            
            T& front();
            
            iterator begin();
            iterator end();
            const_iterator cbegin() const;
            const_iterator cend() const;
            reverse_iterator rbegin();
            reverse_iterator rend();
            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;

            self_type& operator=(const self_type&);
            self_type& operator=(self_type&&);
    };
} // namespace rubbish

#include "deque.cc"

#endif // __RUBBISH_DEQUE__
