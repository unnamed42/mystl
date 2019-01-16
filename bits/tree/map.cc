template <class T1,class T2> constexpr rubbish::map<T1,T2>::map():m_base() {}

template <class T1,class T2> rubbish::map<T1,T2>::map(const map<T1,T2> &o):m_base(o.m_base) {}

template <class T1,class T2> rubbish::map<T1,T2>::map(map<T1,T2> &&o):m_base(std::move(o.m_base)) {}

template <class T1,class T2> rubbish::map<T1,T2>::map(std::initializer_list<value_type>&&l):m_base(std::move(l)) {}

template <class T1,class T2> typename rubbish::map<T1,T2>::iterator rubbish::map<T1,T2>::insert(value_type &&val) {return m_base.insert(std::forward<value_type>(val));}

template <class T1,class T2> template <class key> typename rubbish::map<T1,T2>::const_iterator rubbish::map<T1, T2>::find(key &&k) const {return m_base.find(std::forward<T1>(k));}

template <class T1,class T2> template <class key> typename rubbish::map<T1,T2>::iterator rubbish::map<T1, T2>::find(key &&k) {return m_base.find(std::forward<key>(k));}

template <class T1,class T2> template <class key> void rubbish::map<T1,T2>::erase(key &&k){m_base.erase(std::forward<T1>(k));}

template <class T1,class T2> void rubbish::map<T1,T2>::clear() {m_base.clear();}

template <class T1,class T2> bool rubbish::map<T1,T2>::empty() const noexcept {return m_base.empty();}

template <class T1,class T2> template <class key> T2& rubbish::map<T1,T2>::operator[](key &&val) {
    auto res=find(std::forward<key>(val));
    if(res!=end())
        return res->second;
    return insert({std::forward<key>(val),T2()})->second;
}

template <class T1,class T2> typename rubbish::map<T1,T2>::iterator rubbish::map<T1,T2>::begin() { return m_base.begin();}

template <class T1,class T2> typename rubbish::map<T1,T2>::iterator rubbish::map<T1,T2>::end() { return m_base.end();}

template <class T1,class T2> typename rubbish::map<T1,T2>::const_iterator rubbish::map<T1,T2>::cbegin() const { return m_base.cbegin();}

template <class T1,class T2> typename rubbish::map<T1,T2>::const_iterator rubbish::map<T1,T2>::cend() const { return m_base.cend();}

template <class T1,class T2> typename rubbish::map<T1,T2>::reverse_iterator rubbish::map<T1,T2>::rbegin() { return m_base.rbegin();}

template <class T1,class T2> typename rubbish::map<T1,T2>::reverse_iterator rubbish::map<T1,T2>::rend() { return m_base.rend();}

template <class T1,class T2> typename rubbish::map<T1,T2>::const_reverse_iterator rubbish::map<T1,T2>::crbegin() const { return m_base.crbegin();}

template <class T1,class T2> typename rubbish::map<T1,T2>::const_reverse_iterator rubbish::map<T1,T2>::crend() const { return m_base.crend();}
