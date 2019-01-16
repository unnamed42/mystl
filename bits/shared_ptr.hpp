#ifndef __RUBBISH_SHARED_PTR__
#define __RUBBISH_SHARED_PTR__

#include <cstddef> // std::size_t, std::nullptr_t
#include <bits/move.h> // std::forward
#include "type_traits/remove_qualifier.hpp" // type helpers

namespace rubbish{
    
    template <class T> struct deleter{
        constexpr deleter() noexcept =default;
        
        void operator() (T *ptr) {delete ptr;}
        void operator() (std::nullptr_t) {}
    };
    template <class T> struct deleter<T[]>{
        constexpr deleter() noexcept =default;
        
        void operator() (T *ptr) {delete[] ptr;}
    };
    
    
    template <class T,class Deleter = rubbish::deleter<typename rubbish::remove_reference<T>::type>> class shared_ptr{
        public:
            // memory block definition
            struct block_type{
                typedef typename remove_reference<T>::type* pointer;
                
                pointer ptr;
                std::size_t count;
                
                constexpr block_type():ptr(nullptr),count(0U) {}
                block_type(pointer p):ptr(p),count(1U) {}
            };
            
            typedef shared_ptr<T,Deleter> self_type;
            
        public:
            constexpr explicit shared_ptr(std::nullptr_t);
            
            explicit shared_ptr(T *ptr=nullptr);
            
            // No const here, for we need to modify other.m_manager->count
            shared_ptr(self_type &other);
            
            shared_ptr(self_type &&other);
            
            ~shared_ptr();
            
            // Reset this pointer to nullptr
            void reset();
            
            T& operator*() const;
            
            T* operator->() const;
            
            T& operator[](long n) const;
            
            T* get() const;
            
            Deleter get_deleter() const noexcept;
            
            std::size_t use_count() const;
            
            bool unique() const;
            
            self_type& operator=(self_type &other);
            self_type& operator=(self_type &&other);
            
            operator bool() const;
        private:
            block_type *m_manager;
    };
    
    template <class T,class ...Args>
    inline shared_ptr<T> make_shared(Args&& ...args){
        auto ptr=new raw_type<T>(std::forward<Args>(args)...);
        return shared_ptr<T>(ptr);
    }
    
}  // namespace rubbish

#include "shared_ptr.cc"

#endif // __RUBBISH_SHARED_PTR__
