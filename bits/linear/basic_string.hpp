#ifndef __RUBBISH_BASIC_STRING__
#define __RUBBISH_BASIC_STRING__

#include <cstring> // string manipulation
#include <vector> // result of basic_string<Char>::split
#include "../iterator.hpp"

namespace rubbish {
    
    template <class Char> class basic_string {
        public:
            typedef basic_string<Char> self_type;
            
            class iterator:public rubbish::iterator<std::random_access_iterator_tag,Char>{
                private:
                    typedef rubbish::iterator<std::random_access_iterator_tag,Char> base_class;
                public:
                    typedef typename base_class::reference       reference;
                    typedef typename base_class::pointer         pointer;
                    typedef typename base_class::difference_type difference_type;
                    
                    typedef iterator self_type;
                    typedef Char*    data_type;
                    
                    explicit iterator(const data_type &cursor):m_cursor(cursor) {}
                    iterator(const self_type &o):m_cursor(o.m_cursor) {}
                    ~iterator() {}
                    
                    reference operator*() const {return *m_cursor;}
                    pointer operator->() const {return &operator*();}
                    reference operator[](difference_type n) const {return m_cursor[n];}
                    data_type get() const {return m_cursor;}
                    
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
                    
                    self_type& operator=(const self_type &other) {m_cursor=other.m_cursor;return *this;}
                private:
                    data_type m_cursor;
            };
            
            typedef rubbish::const_iterator<iterator> const_iterator;
            typedef rubbish::reverse_iterator<iterator> reverse_iterator;
            typedef rubbish::const_iterator<reverse_iterator> const_reverse_iterator;
            
        public:
            constexpr basic_string();
            
            basic_string(const Char*);
            
            basic_string(const self_type&);
            
            basic_string(self_type&&);
            
            basic_string(std::size_t count,const Char &val);
            
            ~basic_string();
            
            std::size_t size() const;
            
            bool empty() const;
            
            const Char* base() const;
            
            iterator find(const self_type&,std::size_t pos=0ULL) const;
            iterator find(const Char&,std::size_t pos=0ULL) const;
            
            void replace(const self_type &from,const self_type &to);
            void replace(const Char &from,const Char &to);
            
            std::vector<basic_string<Char>> split(const self_type &delim);
            
            self_type& operator=(const self_type&);
            self_type& operator=(const Char*);
            self_type& operator+=(const self_type&);
            self_type& operator+=(const Char*);
            self_type operator+(const self_type&);
            self_type operator+(const Char*);
            
            iterator begin();
            iterator end();
            const_iterator cbegin() const;
            const_iterator cend() const;
            reverse_iterator rbegin();
            reverse_iterator rend();
            const_reverse_iterator crbegin() const;
            const_reverse_iterator crend() const;
        private:
            Char *m_str;
    };
    
} // namespace rubbish

#include "basic_string.cc"

#endif // __RUBBISH_BASIC_STRING__
