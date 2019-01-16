template <class T> void rubbish::vector<T>::clear() {
    for(auto i=0UL;i<m_used;++i)
        reinterpret_cast<T*>(m_base+i)->~T();
    m_used=0;
}

template <class T> void rubbish::vector<T>::push_back(const T &value){
    if(m_used+1>m_size)
        resize();
    m_base[m_used++]=value;
}

template <class T> void rubbish::vector<T>::pop_back() {
    if(m_used==0)
        return;
    reinterpret_cast<T*>(m_base+(--m_used))->~T();
}

template <class T> void rubbish::vector<T>::resize() {
    if(m_size==0)
        m_size+=rubbish::__vec_base;
    else
        m_size<<=1;
    auto *tmp=new T[m_size];
    for(auto i=0UL;i<m_used;++i)
        tmp[i]=m_base[i];
    delete[] m_base;
    m_base=tmp;
}

template <class T> typename rubbish::vector<T>::self_type& rubbish::vector<T>::operator=(const self_type &other){
    base_class::operator=(other);
    return *this;
}

template <class T> typename rubbish::vector<T>::self_type& rubbish::vector<T>::operator=(self_type &&other){
    base_class::operator=(std::move(other));
    return *this;
}
