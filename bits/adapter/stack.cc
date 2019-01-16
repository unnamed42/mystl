template <class T,class Container> rubbish::stack<T,Container>::stack():m_base() {}

template <class T,class Container> rubbish::stack<T,Container>::stack(const self_type &o):m_base(o.m_base) {}

template <class T,class Container> rubbish::stack<T,Container>::stack(self_type &&o):m_base(std::move(o.m_base)) {}

template <class T,class Container> std::size_t rubbish::stack<T,Container>::size() const noexcept {return m_base.size();}

template <class T,class Container> bool rubbish::stack<T,Container>::empty() const {return m_base.empty();}

template <class T,class Container> void rubbish::stack<T,Container>::push(const T &elem) {m_base.push_back(elem);}

template <class T,class Container> void rubbish::stack<T,Container>::push(T &&elem) {m_base.push_back(std::move(elem));}

template <class T,class Container> T rubbish::stack<T,Container>::top() const {return m_base.back();}

template <class T,class Container> void rubbish::stack<T,Container>::pop() {m_base.pop_back();}

template <class T,class Container> typename rubbish::stack<T,Container>::self_type& rubbish::stack<T,Container>::operator=(const self_type &o) {m_base=o.m_base;return *this;}

template <class T,class Container> typename rubbish::stack<T,Container>::self_type& rubbish::stack<T,Container>::operator=(self_type &&o) {m_base=std::move(o.m_base);return *this;}

template <class T,class Container> typename rubbish::stack<T,Container>::iterator rubbish::stack<T,Container>::begin() {return m_base.begin();}

template <class T,class Container> typename rubbish::stack<T,Container>::iterator rubbish::stack<T,Container>::end() {return m_base.end();}

template <class T,class Container> typename rubbish::stack<T,Container>::const_iterator rubbish::stack<T,Container>::cbegin() const {return m_base.cbegin();}

template <class T,class Container> typename rubbish::stack<T,Container>::const_iterator rubbish::stack<T,Container>::cend() const {return m_base.cend();}

template <class T,class Container> typename rubbish::stack<T,Container>::reverse_iterator rubbish::stack<T,Container>::rbegin() {return m_base.rbegin();}

template <class T,class Container> typename rubbish::stack<T,Container>::reverse_iterator rubbish::stack<T,Container>::rend() {return m_base.rend();}

template <class T,class Container> typename rubbish::stack<T,Container>::const_reverse_iterator rubbish::stack<T,Container>::crbegin() const {return m_base.crbegin();}

template <class T,class Container> typename rubbish::stack<T,Container>::const_reverse_iterator rubbish::stack<T,Container>::crend() const {return m_base.crend();}
