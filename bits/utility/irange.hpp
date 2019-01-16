#ifndef __RUBBISH_IRANGE__
#define __RUBBISH_IRANGE__

#include "../iterator.hpp"

namespace rubbish {
    
    template <class T> class irange:public rubbish::iterator<std::forward_iterator_tag,T>{
        public:
            class iterator{
                private:
                    typedef rubbish::iterator<std::forward_iterator_tag,T> base_class;
                public:
                    typedef typename base_class::value_type        value_type;
                    typedef typename base_class::reference         reference;
                    typedef typename base_class::pointer           pointer;
                    typedef typename base_class::iterator_category iterator_category;
                    
                    typedef iterator self_type;
                    
                    iterator(T _):m_cursor(_) {}
                    reference operator*() {return m_cursor;}
                    pointer operator->() {return &operator*();}
                    self_type& operator++() {++m_cursor;return *this;}
                    self_type operator++(int) {auto i=*this;operator++();return i;}
                    
                    bool operator==(const self_type &o) const {return m_cursor==o.m_cursor;}
                    bool operator<(const self_type &o) const {return m_cursor<o.m_cursor;}
                    bool operator>(const self_type &o) const {return m_cursor>o.m_cursor;}
                    bool operator!=(const self_type &o) const {return !operator==(o);}
                    bool operator<=(const self_type &o) const {return !operator>(o);}
                    bool operator>=(const self_type &o) const {return !operator<(o);}
                private:
                    T m_cursor;
            };
            
            typedef rubbish::const_iterator<iterator> const_iterator;
            
        public:
            irange(T a,T b):m_first(a),m_last(b) {}
            const T& first() const {return m_first;}
            const T& last() const {return m_last;}
            iterator begin() {return iterator(m_first);}
            iterator end() {return iterator(m_last+1);}
            const_iterator cbegin() const {return const_iterator(m_first);}
            const_iterator cend() const {return const_iterator(m_last+1);}
        private:
            T m_first,m_last;
    };
    
    template <class T> inline irange<T> range(T a,T b) {return irange<T>(a,b);}
} // namespace rubbish

#endif // __RUBBISH_IRANGE__
