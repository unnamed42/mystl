#ifndef __CIRCULAR_QUEUE__
#define __CIRCULAR_QUEUE__

#include <cstring> // std::memcpy
#include <stdexcept>

template <class T,std::size_t N> class queue{
    protected:
        T *base;
        std::size_t _rear;          //index of the logical final element
        std::size_t _front;         //index of the logical first element
        std::size_t length;        //current number of elements
    public:
        // Zero-initialization constructor
        queue();
        
        // Copy-constructor
        queue(const queue<T,N>&);
        
        // Move-constructor
        queue(queue<T,N>&&);
        
        // Destructor
        ~queue();
        
        // Return current number of elements
        std::size_t length() const;
        
        // Push an element `elem` to queue rear, if full, throw std::out_of_range
        void push(const T &elem);
        
        // Get an element from queue front, do no boundary check
        T front() const;
        
        // Delete the _front element, if empty, throw std::out_of_range
        void pop();
        
        // Check if the queue is empty
        bool empty() const;
        
        // Check if the queue is full
        bool full() const;
};
template <class T,std::size_t N> queue<T,N>::queue():base(new T[N]),_rear(0),_front(0),length(0){}

template <class T,std::size_t N> queue<T,N>::queue(queue<T,N> &&other){
    base=other.base;
    _rear=other._rear;
    _front=other._front;
    length=other.length;
    other.base=nullptr;
}

template <class T,std::size_t N> queue<T,N>::queue(const queue<T,N> &other){
    _rear=other._rear;
    _front=other._front;
    length=other.length;
    base=new T[N];
    std::memcpy(base,other.base,length*sizeof(T));
}

template <class T,std::size_t N> queue<T,N>::~queue(){delete[] base;}

template <class T,std::size_t N> std::size_t queue<T,N>::length() const {return length;}

template <class T,std::size_t N> void queue<T,N>::push(T elem){
    if(full())
        throw std::out_of_range("queue::push: queue full");
    base[_rear]=elem;
    length++;
    _rear=(_rear+1)%N;
}

template <class T,std::size_t N> T queue<T,N>::front() const { return base[_front]; }

template <class T,std::size_t N> void queue<T,N>::pop(){
    if(empty())
        throw std::out_of_range("queue::front: queue empty");
    _front=(_front+1)%N;
    length--;
}

template <class T,std::size_t N> bool queue<T,N>::empty() const{return length==0;}

template <class T,std::size_t N> bool queue<T,N>::full() const{return length>=N;} 

#endif
