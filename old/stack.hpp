#ifndef __STACK__
#define __STACK__

#include <cstring>
#include <stdexcept>

template <class T> class stack{
    protected:
        T *base;
        T *_top;
        std::size_t size;
    public:
        // Construct a stack of length `length`
        explicit stack(std::size_t _size=0);
        
        // Move-constructor
        stack(stack<T> &&);
        
        // Copy-constructor
        stack(const stack<T>&);
        
        // Destructor
        ~stack();
        
        // Return length of this stack
        std::size_t length() const;
        
        // Clear this stack
        void clear();
        
        // Resize this stack
        void resize(std::size_t _size);
        
        // Push element `data` into stack top
        void push(const T &data);
        
        // Check if the stack is empty 
        bool empty() const;
        
        // Delete the element at stack top
        void pop();
        
        // Get the element at stack top
        T top() const;
};
template <class T> stack<T>::stack(std::size_t _size){base=_top=new T[size=_size]();}

template <class T> stack<T>::stack(stack &&other){
    base=other.base;
    _top=other._top;
    size=other.size;
    other.base=other._top=NULL;
}

template <class T> stack<T>::~stack(){delete[] base;}

template <class T> std::size_t stack<T>::length() const{return _top-base;}

template <class T> bool stack<T>::empty() const{return _top==base;}

template <class T> void stack<T>::clear(){_top=base;}

template <class T> void stack<T>::resize(std::size_t _size){
    if(base==NULL)
        base=_top=new T[size=_size]();
    else{
        void *temp=std::realloc(base,_size*sizeof(T));
        if(temp==NULL)
            throw std::bad_alloc();
        base=static_cast<T*>(temp);size=_size;
    }
}

template <class T> void stack<T>::push(const T &data){
    if(_top-base>=size)
        resize(size+10);
    *(_top++)=data;
}

template <class T> T& stack<T>::pop(){
    if(_top!=base)
        return *(--_top);
    throw std::out_of_range("Stack empty");
}

template <class T> const T& stack<T>::top() const{
    if(_top!=base)
        return *(_top-1);
    throw std::out_of_range("Stack empty");
}

#endif

