template <class T> constexpr rubbish::continuous_container<T>::continuous_container():m_base(nullptr),m_size(0),m_used(0) {}

template <class T> rubbish::continuous_container<T>::continuous_container(std::initializer_list<T> &&l):m_base(nullptr),m_size(0),m_used(0) {
    auto size=l.size();
    if(size==0)
        return;
    m_size=size;
    m_base=new T[size];
    for(auto &&i:l)
        m_base[m_used++]=i;
}

template <class T> rubbish::continuous_container<T>::continuous_container(self_type &&o):m_base(o.m_base),m_size(o.m_size),m_used(o.m_used) {o.m_base=nullptr;}

template <class T> rubbish::continuous_container<T>::continuous_container(const self_type &o):m_base(nullptr),m_size(o.m_size),m_used(0) {
    for(;m_used<m_size;++m_used)
        m_base[m_used]=o.m_base[m_used];
}

template <class T> rubbish::continuous_container<T>::continuous_container(std::size_t count,const T &value):m_base(nullptr),m_size(count),m_used(count) {
    if(count==0)
        m_base=nullptr;
    m_base=new T[count];
    for(auto i=0UL;i<count;++i)
        m_base[i]=value;
}

template <class T> rubbish::continuous_container<T>::~continuous_container() {delete[] m_base;}

template <class T> std::size_t rubbish::continuous_container<T>::capacity() const noexcept {return m_size;}

template <class T> std::size_t rubbish::continuous_container<T>::size() const noexcept {return m_used;}

template <class T> typename rubbish::continuous_container<T>::self_type& rubbish::continuous_container<T>::operator=(const self_type &o) {
    this->~continuous_container();
    m_size=o.m_size;
    m_base=new T[m_size];
    for(;m_used<m_size;++m_used)
        m_base[m_used]=o.m_base[m_used];
    return *this;
}

template <class T> typename rubbish::continuous_container<T>::self_type& rubbish::continuous_container<T>::operator=(self_type &&o) {
    this->~continuous_container();
    m_size=o.m_size;
    m_base=o.m_base;
    m_used=o.m_used;
    o.m_base=nullptr;
    o.m_size=o.m_used=0;
    return *this;
}

template <class T> typename rubbish::continuous_container<T>::iterator rubbish::continuous_container<T>::begin() {return iterator(m_base);}

template <class T> typename rubbish::continuous_container<T>::iterator rubbish::continuous_container<T>::end() {return iterator(m_base+m_used);}

template <class T> typename rubbish::continuous_container<T>::const_iterator rubbish::continuous_container<T>::cbegin() const {return const_iterator(const_cast<continuous_container<T>*>(this)->begin());}

template <class T> typename rubbish::continuous_container<T>::const_iterator rubbish::continuous_container<T>::cend() const {return const_iterator(const_cast<continuous_container<T>*>(this)->end());}

template <class T> typename rubbish::continuous_container<T>::reverse_iterator rubbish::continuous_container<T>::rbegin() {return reverse_iterator(end());}

template <class T> typename rubbish::continuous_container<T>::reverse_iterator rubbish::continuous_container<T>::rend() {return reverse_iterator(begin());}

template <class T> typename rubbish::continuous_container<T>::const_reverse_iterator rubbish::continuous_container<T>::crbegin() const {return const_reverse_iterator(const_cast<continuous_container<T>*>(this)->rbegin());}

template <class T> typename rubbish::continuous_container<T>::const_reverse_iterator rubbish::continuous_container<T>::crend() const {return const_reverse_iterator(const_cast<continuous_container<T>*>(this)->rend());}
