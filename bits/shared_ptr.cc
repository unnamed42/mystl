template <class T,class Deleter> constexpr rubbish::shared_ptr<T,Deleter>::shared_ptr(std::nullptr_t):m_manager(nullptr) {}

template <class T,class Deleter> rubbish::shared_ptr<T,Deleter>::shared_ptr(T *ptr):m_manager(nullptr) {m_manager=new block_type(ptr);}

template <class T,class Deleter> rubbish::shared_ptr<T,Deleter>::shared_ptr(self_type &o):m_manager(o.m_manager) {
    if(m_manager!=nullptr)
        ++m_manager->count;
}

template <class T,class Deleter> rubbish::shared_ptr<T,Deleter>::shared_ptr(self_type &&o):m_manager(o.m_manager) {o.m_manager=nullptr;}

template <class T,class Deleter> rubbish::shared_ptr<T,Deleter>::~shared_ptr() {reset();}

template <class T,class Deleter> void rubbish::shared_ptr<T,Deleter>::reset() {
    if(m_manager==nullptr)
        return;
    if((--m_manager->count)==0){
        auto &&deleter=Deleter();
        deleter(m_manager->ptr);
        delete m_manager;
    }
    m_manager=nullptr;
}

template <class T,class Deleter> T& rubbish::shared_ptr<T,Deleter>::operator*() const {return *(m_manager->ptr);}

template <class T,class Deleter> T* rubbish::shared_ptr<T,Deleter>::operator->() const {return &operator*();}

template <class T,class Deleter> T& rubbish::shared_ptr<T,Deleter>::operator[](long n) const {return (m_manager->ptr)[n];}

template <class T,class Deleter> T* rubbish::shared_ptr<T,Deleter>::get() const {return m_manager==nullptr?nullptr:m_manager->ptr;}

template <class T,class Deleter> Deleter rubbish::shared_ptr<T,Deleter>::get_deleter() const noexcept {return Deleter();}

template <class T,class Deleter> std::size_t rubbish::shared_ptr<T,Deleter>::use_count() const {return m_manager==nullptr?0:m_manager->count;}

template <class T,class Deleter> bool rubbish::shared_ptr<T,Deleter>::unique() const {return m_manager!=nullptr && m_manager->count==1;}

template <class T,class Deleter> rubbish::shared_ptr<T,Deleter>::operator bool() const {return m_manager!=nullptr && m_manager->ptr!=nullptr;}

template <class T,class Deleter> typename rubbish::shared_ptr<T,Deleter>::self_type& rubbish::shared_ptr<T,Deleter>::operator=(self_type &o) {
    m_manager=o.m_manager;
    if(m_manager!=nullptr)
        ++m_manager->count;
    return *this;
}

template <class T,class Deleter> typename rubbish::shared_ptr<T,Deleter>::self_type& rubbish::shared_ptr<T,Deleter>::operator=(self_type &&o) {
    m_manager=o.m_manager;
    o.m_manager=nullptr;
    return *this;
}

template <class T,class Deleter> bool operator<(const rubbish::shared_ptr<T,Deleter> &lhs,const T *rhs) {return lhs.get()<rhs;}
template <class T,class Deleter> bool operator>(const rubbish::shared_ptr<T,Deleter> &lhs,const T *rhs) {return lhs.get()>rhs;}
template <class T,class Deleter> bool operator==(const rubbish::shared_ptr<T,Deleter> &lhs,const T *rhs) {return lhs==rhs;}
template <class T,class Deleter> bool operator<=(const rubbish::shared_ptr<T,Deleter> &lhs,const T *rhs) {return !(lhs>rhs);}
template <class T,class Deleter> bool operator>=(const rubbish::shared_ptr<T,Deleter> &lhs,const T *rhs) {return !(lhs<rhs);}
template <class T,class Deleter> bool operator!=(const rubbish::shared_ptr<T,Deleter> &lhs,const T *rhs) {return !(lhs==rhs);}
template <class T,class Deleter> bool operator<(const T *lhs,const rubbish::shared_ptr<T,Deleter> &rhs) {return rhs>lhs;}
template <class T,class Deleter> bool operator>(const T *lhs,const rubbish::shared_ptr<T,Deleter> &rhs) {return rhs<lhs;}
template <class T,class Deleter> bool operator==(const T *lhs,const rubbish::shared_ptr<T,Deleter> &rhs) {return rhs==lhs;}
template <class T,class Deleter> bool operator<=(const T *lhs,const rubbish::shared_ptr<T,Deleter> &rhs) {return rhs>=lhs;}
template <class T,class Deleter> bool operator>=(const T *lhs,const rubbish::shared_ptr<T,Deleter> &rhs) {return rhs<=lhs;}
template <class T,class Deleter> bool operator!=(const T *lhs,const rubbish::shared_ptr<T,Deleter> &rhs) {return rhs!=lhs;}
