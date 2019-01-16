#ifndef __RUBBISH_ITERATOR__
#define __RUBBISH_ITERATOR__

#include <cstddef> // std::ptrdiff_t
#include <bits/stl_iterator_base_types.h> // std iterator tags
#include <bits/move.h> // std::move
#include "type_traits/remove_qualifier.hpp"

namespace rubbish{
    
    template<class Category,class T,class Distance = std::ptrdiff_t,
             class Pointer = T*,class Reference = T& > 
    struct iterator{
        typedef typename remove_const<T>::type value_type;
        typedef Pointer                        pointer;
        typedef Reference                      reference;
        typedef Distance                       difference_type;
        typedef Category                       iterator_category;
    };
    
    template <class Iterator> struct iterator_traits{
        typedef typename Iterator::value_type        value_type;
        typedef typename Iterator::pointer           pointer;
        typedef typename Iterator::reference         reference;
        typedef typename Iterator::difference_type   difference_type;
        typedef typename Iterator::iterator_category iterator_category;
    };
    template <class T> struct iterator_traits<T*>{
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };
    template <class T> struct iterator_traits<const T*>{
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::ptrdiff_t                  difference_type;
        typedef std::random_access_iterator_tag iterator_category;
    };
    
    // `Iterator` must at least satisfies BidirectionalIterator
    template <class Iterator> class reverse_iterator{
        private:
            typedef iterator_traits<Iterator> traits_type;
        public:
            typedef typename traits_type::value_type        value_type;
            typedef typename traits_type::pointer           pointer;
            typedef typename traits_type::reference         reference;
            typedef typename traits_type::difference_type   difference_type;
            typedef typename traits_type::iterator_category iterator_category;
            
            typedef reverse_iterator<Iterator> self_type;
            
            explicit reverse_iterator(const Iterator &iter):m_iter(iter) {}
            explicit reverse_iterator(Iterator &&iter):m_iter(std::move(iter)) {}
            reverse_iterator(const self_type &other):m_iter(other.m_iter) {}
            reverse_iterator(self_type &&other):m_iter(std::move(other.m_iter)) {}
            virtual ~reverse_iterator() {}
            
            reference operator*() const {return *(m_iter-1);}
            pointer operator->() const {return &operator*();}
            reference operator[](difference_type n) const {return m_iter[-n-1];}
            Iterator base() const {return m_iter;}
            
            self_type& operator++() {--m_iter;return *this;}
            self_type operator++(int) {auto i=*this;operator++();return i;}
            self_type& operator--() {++m_iter;return *this;}
            self_type operator--(int) {auto i=*this;operator--();return i;}
            self_type& operator+=(const difference_type &diff) {m_iter-=diff;return *this;}
            self_type operator+(const difference_type &diff) const {return self_type(m_iter-diff);}
            self_type& operator-=(const difference_type &diff) {m_iter+=diff;return *this;}
            self_type operator-(const difference_type &diff) const {return self_type(m_iter+diff);}
            
            self_type& operator=(const Iterator &iter) {m_iter=iter;return *this;}
            self_type& operator=(Iterator &&iter) {m_iter=std::move(iter);return *this;}
            self_type& operator=(const self_type &other) {m_iter=other.m_iter;return *this;}
            self_type& operator=(self_type &&other) {m_iter=std::move(other.m_iter);return *this;}
        protected:
            Iterator m_iter;
    };
    template <class IteratorL,class IteratorR> inline bool operator<(const reverse_iterator<IteratorL> &lhs,const reverse_iterator<IteratorR> &rhs) {return lhs.base()<rhs.base();}
    template <class IteratorL,class IteratorR> inline bool operator>(const reverse_iterator<IteratorL> &lhs,const reverse_iterator<IteratorR> &rhs) {return rhs<lhs;}
    template <class IteratorL,class IteratorR> inline bool operator<=(const reverse_iterator<IteratorL> &lhs,const reverse_iterator<IteratorR> &rhs) {return !(lhs>rhs);}
    template <class IteratorL,class IteratorR> inline bool operator>=(const reverse_iterator<IteratorL> &lhs,const reverse_iterator<IteratorR> &rhs) {return !(lhs<rhs);}
    template <class IteratorL,class IteratorR> inline bool operator==(const reverse_iterator<IteratorL> &lhs,const reverse_iterator<IteratorR> &rhs) {return lhs.base()==rhs.base();}
    template <class IteratorL,class IteratorR> inline bool operator!=(const reverse_iterator<IteratorL> &lhs,const reverse_iterator<IteratorR> &rhs) {return !(lhs==rhs);}
    
    template <class Iterator> class const_iterator{
        private:
            typedef iterator_traits<Iterator> traits_type;
        public:
            typedef typename traits_type::value_type                                        value_type;
            typedef const typename remove_pointer<typename traits_type::pointer>::type*     pointer;
            typedef const typename remove_reference<typename traits_type::reference>::type& reference;
            typedef typename traits_type::difference_type                                   difference_type;
            typedef typename traits_type::iterator_category                                 iterator_category;
            
            typedef const_iterator<Iterator> self_type;
            
            explicit const_iterator(const Iterator &iter):m_iter(iter) {}
            explicit const_iterator(Iterator &&iter):m_iter(std::move(iter)) {}
            const_iterator(const self_type &other):m_iter(other.m_iter) {}
            const_iterator(self_type &&other):m_iter(std::move(other.m_iter)) {}
            ~const_iterator() {}
            
            reference operator*() const {return static_cast<reference>(*m_iter);}
            pointer operator->() const {return static_cast<pointer>(&operator*());}
            reference operator[](difference_type n) const {return static_cast<reference>(m_iter[n]);}
            Iterator base() const {return m_iter;}
            
            self_type& operator++() {++m_iter;return *this;}
            self_type operator++(int) {auto i=*this;operator++();return i;}
            self_type& operator--() {--m_iter;return *this;}
            self_type operator--(int) {auto i=*this;operator--();return i;}
            self_type& operator+=(const difference_type &diff) {m_iter+=diff;return *this;}
            self_type operator+(const difference_type &diff) const {return self_type(m_iter+diff);}
            self_type& operator-=(const difference_type &diff) {m_iter-=diff;return *this;}
            self_type operator-(const difference_type &diff) const {return self_type(m_iter-diff);}
            
            self_type& operator=(const Iterator &iter) {m_iter=iter;return *this;}
            self_type& operator=(Iterator &&iter) {m_iter=std::move(iter);return *this;}
            self_type& operator=(const self_type &other) {m_iter=other.m_iter;return *this;}
            self_type& operator=(self_type &&other) {m_iter=std::move(other.m_iter);return *this;}
        private:
            Iterator m_iter;
    };
    template <class IteratorL,class IteratorR> inline bool operator<(const const_iterator<IteratorL> &lhs,const const_iterator<IteratorR> &rhs) {return lhs.base()<rhs.base();}
    template <class IteratorL,class IteratorR> inline bool operator>(const const_iterator<IteratorL> &lhs,const const_iterator<IteratorR> &rhs) {return rhs<lhs;}
    template <class IteratorL,class IteratorR> inline bool operator<=(const const_iterator<IteratorL> &lhs,const const_iterator<IteratorR> &rhs) {return !(lhs>rhs);}
    template <class IteratorL,class IteratorR> inline bool operator>=(const const_iterator<IteratorL> &lhs,const const_iterator<IteratorR> &rhs) {return !(lhs<rhs);}
    template <class IteratorL,class IteratorR> inline bool operator==(const const_iterator<IteratorL> &lhs,const const_iterator<IteratorR> &rhs) {return lhs.base()==rhs.base();}
    template <class IteratorL,class IteratorR> inline bool operator!=(const const_iterator<IteratorL> &lhs,const const_iterator<IteratorR> &rhs) {return !(lhs==rhs);}
    // Make const_iterator and Iterator co-operable
    template <class Iterator> inline bool operator<(const Iterator &lhs,const const_iterator<Iterator> &rhs) {return lhs<rhs.base();}
    template <class Iterator> inline bool operator>(const Iterator &lhs,const const_iterator<Iterator> &rhs) {return lhs>rhs.base();}
    template <class Iterator> inline bool operator<=(const Iterator &lhs,const const_iterator<Iterator> &rhs) {return !(lhs>rhs);}
    template <class Iterator> inline bool operator>=(const Iterator &lhs,const const_iterator<Iterator> &rhs) {return !(lhs<rhs);}
    template <class Iterator> inline bool operator==(const Iterator &lhs,const const_iterator<Iterator> &rhs) {return lhs==rhs.base();}
    template <class Iterator> inline bool operator!=(const Iterator &lhs,const const_iterator<Iterator> &rhs) {return !(lhs==rhs);}
    template <class Iterator> inline bool operator<(const const_iterator<Iterator> &lhs,const Iterator &rhs) {return rhs>lhs;}
    template <class Iterator> inline bool operator>(const const_iterator<Iterator> &lhs,const Iterator &rhs) {return rhs<lhs;}
    template <class Iterator> inline bool operator<=(const const_iterator<Iterator> &lhs,const Iterator &rhs) {return rhs>=lhs;}
    template <class Iterator> inline bool operator>=(const const_iterator<Iterator> &lhs,const Iterator &rhs) {return rhs<=lhs;}
    template <class Iterator> inline bool operator==(const const_iterator<Iterator> &lhs,const Iterator &rhs) {return rhs==lhs;}
    template <class Iterator> inline bool operator!=(const const_iterator<Iterator> &lhs,const Iterator &rhs) {return rhs!=lhs;}

} // namespace rubbish

#endif // __RUBBISH_ITERATOR__
