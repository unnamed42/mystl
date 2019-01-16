template <class T> rubbish::deque<T>::deque():m_map(nullptr),m_msize(0),m_start({0,0}),m_end({0,0}) {}

template <class T> rubbish::deque<T>::deque(const deque<T> &o):m_map(nullptr),m_msize(o.m_msize),m_start(o.m_start),m_end(o.m_end) {
    m_map=new T*[m_msize];
    for(auto i=0U;i<m_msize;++i){
        m_map[i]=new T[__deque_block];
        for(auto j=0U;j<__deque_block;++j)
            m_map[i][j]=o.m_map[i][j];
    }
}

template <class T> rubbish::deque<T>::deque(deque<T> &&o):m_map(o.m_map),m_msize(o.m_msize),m_start(o.m_start),m_end(o.m_end) {o.m_map=nullptr;}

template <class T> rubbish::deque<T>::~deque() {
    for(auto i=0U;i<m_msize;++i)
        delete[] m_map[i];
    delete[] m_map;
}

template <class T> typename rubbish::deque<T>::self_type& rubbish::deque<T>::operator=(const self_type &o) {
    this->~deque();
    m_map=new T*[m_msize];
    for(auto i=0U;i<m_msize;++i){
        m_map[i]=new T[__deque_block];
        for(auto j=0U;j<__deque_block;++j)
            m_map[i][j]=o.m_map[i][j];
    }
    return *this;
}

template <class T> typename rubbish::deque<T>::self_type& rubbish::deque<T>::operator=(self_type &&o) {
    this->~deque();
    m_map=o.m_map;
    m_start=std::move(o.m_start);
    m_end=std::move(o.m_end);
    m_msize=o.m_msize;
    o.m_map=nullptr;
    return *this;
}

template <class T> typename rubbish::deque<T>::const_iterator rubbish::deque<T>::cbegin() const {return const_iterator(const_cast<deque<T>*>(this)->begin());}

template <class T> typename rubbish::deque<T>::const_iterator rubbish::deque<T>::cend() const {return const_iterator(const_cast<deque<T>*>(this)->end());}

template <class T> typename rubbish::deque<T>::reverse_iterator rubbish::deque<T>::rbegin() {return reverse_iterator(begin());}

template <class T> typename rubbish::deque<T>::reverse_iterator rubbish::deque<T>::rend() {return reverse_iterator(rend());}

template <class T> typename rubbish::deque<T>::const_reverse_iterator rubbish::deque<T>::crbegin() const {return const_reverse_iterator(const_cast<deque<T>*>(this)->rbegin());}

template <class T> typename rubbish::deque<T>::const_reverse_iterator rubbish::deque<T>::crend() const {return const_reverse_iterator(const_cast<deque<T>*>(this)->rend());}

