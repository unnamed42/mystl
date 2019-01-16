template<class T,std::size_t N> rubbish::array<T, N>::array():m_base(new T[N]()),m_occupied(0) {}


template <class T,std::size_t N> rubbish::array<T,N>::array(std::size_t count,const T &value):m_base(new T[N]),m_occupied(0){
    if(count>N)
        count=N;
    for(;m_occupied<=count;++m_occupied)
        m_base[m_occupied]=value;
}

template <class T,std::size_t N> rubbish::array<T,N>::array(const T (&arr)[N]):m_base(nullptr),m_occupied(N){
    m_base=new T[N];
    std::memcpy(m_base,arr,N*sizeof(T));
}

template <class T,std::size_t N> rubbish::array<T,N>::array(rubbish::array<T,N> &&arr) {
    m_base = arr.m_base;
    m_occupied = arr.m_occupied;
    arr.m_base = nullptr;
}

template <class T,std::size_t N> rubbish::array<T,N>::array(const rubbish::array<T,N> &arr) {
    m_base = new T[N];
    m_occupied = arr.m_occupied;
    std::memcpy(m_base,arr.m_base,m_occupied*sizeof(T));
}

template <class T,std::size_t N> rubbish::array<T,N>::array(std::initializer_list<T> &&l){
    m_base=new T[l.size()]();
    m_occupied=0;
    for(auto &&i:l)
        m_base[m_occupied++]=i;
}

template <class T,std::size_t N> rubbish::array<T,N>::~array(){delete[] m_base;}

template <class T,std::size_t N> std::size_t rubbish::array<T,N>::capacity() const noexcept {return N;}

template <class T,std::size_t N> std::size_t rubbish::array<T,N>::size() const noexcept {return m_occupied;}

template <class T,std::size_t N> bool rubbish::array<T,N>::empty() const noexcept {return m_occupied==0;}

template <class T,std::size_t N> typename rubbish::array<T,N>::iterator rubbish::array<T,N>::begin() {return iterator(m_base);}

template <class T,std::size_t N> typename rubbish::array<T,N>::iterator rubbish::array<T,N>::end() {return iterator(m_base+m_occupied);}

template <class T,std::size_t N> typename rubbish::array<T,N>::const_iterator rubbish::array<T,N>::cbegin() const {return const_iterator(m_base);}

template <class T,std::size_t N> typename rubbish::array<T,N>::const_iterator rubbish::array<T,N>::cend() const {return const_iterator(m_base+m_occupied);}

template <class T,std::size_t N> void rubbish::array<T,N>::push_back(const T &element){
    if(m_occupied+1>N)
        throw std::out_of_range("array::push_back: array is full");
    m_base[m_occupied++]=element;
}

template <class T,std::size_t N> void rubbish::array<T,N>::pop_back() {
    if(m_occupied==0)
        return;
    (m_base+(--m_occupied))->~T();
}

template <class T,std::size_t N> T& rubbish::array<T,N>::back() {return *(m_base+m_occupied-1);}

template <class T,std::size_t N> T& rubbish::array<T,N>::front() {return *m_base;}

template <class T,std::size_t N> void rubbish::array<T,N>::insert(std::size_t index,const T &element){
    if(m_occupied+1>N||index>m_occupied)
        throw std::out_of_range("array::insert: array is full");
    for(auto i=m_occupied;i>index;i--)
        m_base[i]^=m_base[i-1]^=m_base[i]^=m_base[i-1];
    m_base[index]=element;
    m_occupied++;
}

template <class T,std::size_t N> void rubbish::array<T,N>::remove_elem(const T &element){
    for(auto i=0UL;i<m_occupied;i++){
        if(m_base[i]==element){
            for(auto j=i;j<m_occupied-1;j++)
                m_base[j]^=m_base[j+1]^=m_base[j]^=m_base[j+1];
            m_occupied--;
            i--;
        }
    }
}

template <class T,std::size_t N> T& rubbish::array<T,N>::operator[](std::size_t index) const {
    if(index>=N)
        throw std::out_of_range("array::operator[]: index too large");
    return m_base[index];
}
