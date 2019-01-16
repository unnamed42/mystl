template <class T,class Container> rubbish::queue<T,Container>::queue():m_base() {}

template <class T,class Container> rubbish::queue<T,Container>::queue(const self_type &o):m_base(o.m_base) {}

template <class T,class Container> rubbish::queue<T,Container>::queue(self_type &&o):m_base(std::move(o.m_base)) {}

template <class T,class Container> std::size_t rubbish::queue<T,Container>::size() const {return m_base.size();}

template <class T,class Container> bool rubbish::queue<T,Container>::empty() const {return m_base.empty();}

template <class T,class Container> void rubbish::queue<T,Container>::push(const T &elem) {m_base.push_back(elem);}

template <class T,class Container> void rubbish::queue<T,Container>::push(T &&elem) {m_base.push_back(std::move(elem));}

template <class T,class Container> void rubbish::queue<T,Container>::pop() {m_base.pop_front();}

template <class T,class Container> T rubbish::queue<T,Container>::front() const {return m_base.front();}

template <class T,class Container> typename rubbish::queue<T,Container>::self_type& rubbish::queue<T,Container>::operator=(const self_type &o) {m_base=o.m_base;return *this;}

template <class T,class Container> typename rubbish::queue<T,Container>::self_type& rubbish::queue<T,Container>::operator=(self_type &&o) {m_base=std::move(o.m_base);return *this;}

template <class T,class Container> typename rubbish::queue<T,Container>::iterator rubbish::queue<T,Container>::begin() {return m_base.begin();}

template <class T,class Container> typename rubbish::queue<T,Container>::iterator rubbish::queue<T,Container>::end() {return m_base.end();}

template <class T,class Container> typename rubbish::queue<T,Container>::const_iterator rubbish::queue<T,Container>::cbegin() const {return m_base.cbegin();}

template <class T,class Container> typename rubbish::queue<T,Container>::const_iterator rubbish::queue<T,Container>::cend() const {return m_base.cend();}

template <class T,class Container> typename rubbish::queue<T,Container>::reverse_iterator rubbish::queue<T,Container>::rbegin() {return m_base.rbegin();}

template <class T,class Container> typename rubbish::queue<T,Container>::reverse_iterator rubbish::queue<T,Container>::rend() {return m_base.rend();}

template <class T,class Container> typename rubbish::queue<T,Container>::const_reverse_iterator rubbish::queue<T,Container>::crbegin() const {return m_base.crbegin();}

template <class T,class Container> typename rubbish::queue<T,Container>::const_reverse_iterator rubbish::queue<T,Container>::crend() const {return m_base.crend();}
