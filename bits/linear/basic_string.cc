template <class Char> constexpr rubbish::basic_string<Char>::basic_string():m_str(nullptr) {}

template <class Char> rubbish::basic_string<Char>::basic_string(const Char *src):m_str(nullptr) {
    m_str=new Char[std::strlen(src)+1];
    std::strcpy(m_str,src);
}

template <class Char> rubbish::basic_string<Char>::basic_string(const self_type &o):m_str(nullptr) {
    m_str=new Char[o.size()+1];
    std::strcpy(m_str,o.m_str);
}

template <class Char> rubbish::basic_string<Char>::basic_string(self_type &&o):m_str(o.m_str) {o.m_str=nullptr;}

template <class Char> rubbish::basic_string<Char>::basic_string(std::size_t count,const Char &val):m_str(nullptr) {
    m_str=new Char[count+1];
    std::memcpy(m_str,&val,sizeof(Char));
    m_str[count]='\0';
}

template <class Char> rubbish::basic_string<Char>::~basic_string() {delete[] m_str;}

template <class Char> std::size_t rubbish::basic_string<Char>::size() const {return empty()?0ULL:std::strlen(m_str);}

template <class Char> bool rubbish::basic_string<Char>::empty() const {return m_str==nullptr;}

template <class Char> const Char* rubbish::basic_string<Char>::base() const {return static_cast<const Char*>(m_str);}

template <class Char> typename rubbish::basic_string<Char>::iterator rubbish::basic_string<Char>::begin() {return iterator(m_str);}

template <class Char> typename rubbish::basic_string<Char>::iterator rubbish::basic_string<Char>::end() {return iterator(m_str+size());}

template <class Char> typename rubbish::basic_string<Char>::const_iterator rubbish::basic_string<Char>::cbegin() const {return const_iterator(const_cast<basic_string<Char>*>(this)->begin());}

template <class Char> typename rubbish::basic_string<Char>::const_iterator rubbish::basic_string<Char>::cend() const {return const_iterator(const_cast<basic_string<Char>*>(this)->end());}

template <class Char> typename rubbish::basic_string<Char>::reverse_iterator rubbish::basic_string<Char>::rbegin() {return reverse_iterator(end());}

template <class Char> typename rubbish::basic_string<Char>::reverse_iterator rubbish::basic_string<Char>::rend() {return reverse_iterator(begin());}

template <class Char> typename rubbish::basic_string<Char>::const_reverse_iterator rubbish::basic_string<Char>::crbegin() const {return const_reverse_iterator(const_cast<basic_string<Char>*>(this)->rbegin());}

template <class Char> typename rubbish::basic_string<Char>::const_reverse_iterator rubbish::basic_string<Char>::crend() const {return const_reverse_iterator(const_cast<basic_string<Char>*>(this)->rend());}
