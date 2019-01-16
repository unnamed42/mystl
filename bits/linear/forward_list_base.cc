namespace rubbish{
    
    namespace helper{
        // Helper function of forward_list_base<T,Node>::sort()
        template <class Node> Node* forward_list_merge(Node *h1,Node *h2){
            if(h1==h2)
                return h1;
            Node *head,**ptr=&head;
            while(h1!=nullptr&&h2!=nullptr){
                if(h1->data<h2->data){
                    *ptr=h1;
                    h1=h1->next;
                } else {
                    *ptr=h2;
                    h2=h2->next;
                }
                ptr=&(*ptr)->next;
            }
            if(h1!=nullptr)
                *ptr=h1;
            if(h2!=nullptr)
                *ptr=h2;
            return head;
        }
        
        template <class Node> Node* forward_list_merge_sort(Node *head){
            if(head==nullptr||head->next==nullptr)
                return head;
            if(head->next->next==nullptr){
                Node *next=head->next;
                if(next->data<head->data){
                    next->next=head;
                    head->next=nullptr;
                    head=next;
                }
                return head;
            }
            Node *slow=head,*fast=head->next->next;
            while(fast!=nullptr){
                slow=slow->next;
                fast=fast->next;
                if(fast!=nullptr)
                    fast=fast->next;
            }
            // Reuse fast
            fast=forward_list_merge_sort<Node>(slow->next);
            slow->next=nullptr;
            return forward_list_merge<Node>(forward_list_merge_sort<Node>(head),fast);
        }
        
    } // namespace helper
    
} // namespace rubbish

template <class T,class Node> constexpr rubbish::forward_list_base<T,Node>::forward_list_base():m_head(nullptr),m_end(nullptr),m_length(0) {}

template <class T,class Node> rubbish::forward_list_base<T,Node>::forward_list_base(std::size_t len,const T &value):m_head(nullptr),m_end(nullptr),m_length(len){
    if(len==0)
        return;
    m_end=m_head=new node(value);
    for(;len>1;len--){
        m_end->next=new node(value);
        m_end=m_end->next;
    }
}

template <class T,class Node> rubbish::forward_list_base<T,Node>::forward_list_base(rubbish::forward_list_base<T,Node> &&other):m_head(other.m_head),m_end(other.m_end),m_length(other.m_length) {other.m_head=other.m_end=nullptr;other.m_length=0;}

template <class T,class Node> rubbish::forward_list_base<T,Node>::forward_list_base(const rubbish::forward_list_base<T,Node> &other):m_head(nullptr),m_end(nullptr),m_length(other.m_length){
    if(other.empty())
        return;
    node **ptr=&m_head;const node *optr=other.m_head;
    *ptr=new node(*optr); optr=optr->next;
    while(optr!=nullptr){
        (*ptr)->next=new node(*optr);
        ptr=&(*ptr)->next;
        optr=optr->next;
    }
    m_end=*ptr;
}

template <class T,class Node> rubbish::forward_list_base<T,Node>::forward_list_base(std::initializer_list<T> &&l):m_head(nullptr),m_end(nullptr),m_length(0){
    if(l.size()==0)
        return;
    auto it=l.begin();
    m_head=m_end=new node(*(it++));
    for(;it!=l.end();++it){
        m_end->next=new node(*it);
        m_end=m_end->next;
    }
}

template <class T,class Node> rubbish::forward_list_base<T,Node>::~forward_list_base(){
    while(m_head!=nullptr){
        m_end=m_head->next;
        delete m_head;
        m_head=m_end;
    }
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::remove_elem(const T &elem){
    if(m_head->data==elem){
        if(m_head->next==nullptr){
            delete m_head;
            m_length--;
            m_head=nullptr;
            return;
        }
        node *ptr=m_head->next;
        delete m_head;
        m_length--;
        m_head=ptr;
        this->remove_elem(elem);
    }
    node *ptr=m_head->next,*prev=m_head;
    while(ptr!=nullptr){
        if(ptr->elem==elem){
            prev->next=ptr->next;
            delete ptr;
            m_length--;
            ptr=prev->next;
        } else {
            prev=ptr;
            ptr=ptr->next;
        }
    }
    if(prev->next==nullptr)
        m_end=prev;
}

template <class T,class Node> bool rubbish::forward_list_base<T,Node>::empty() const {return m_head==nullptr;}

template <class T,class Node> std::size_t rubbish::forward_list_base<T,Node>::size() const noexcept {return m_length;}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::sort() {
    m_head=helper::forward_list_merge_sort<Node>(m_head);
    auto ptr=m_head;
    while(ptr->next!=nullptr)
        ptr=ptr->next;
    m_end=ptr;
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::clear() {
    this->~forward_list_base();
    m_head=m_end=nullptr;
    m_length=0;
}

template <class T,class Node> typename rubbish::forward_list_base<T,Node>::iterator rubbish::forward_list_base<T,Node>::search(const T &elem) const{
    node *p=m_head;
    while(p!=nullptr){
        if(p->data==elem)
            return iterator(p);
        p=p->next;
    }
    return iterator(nullptr);
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::insert_after(iterator it,const T &elem){
    node const *_it=it.get();
    if(_it==nullptr)
        return;
    if(_it==m_end){
        m_end->next=new node(elem);
        m_end=m_end->next;
    } else {
        node *temp=new node(elem);
        temp->next=_it->next;
        _it->next=temp;
    }
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::push_back(const T &elem){
    ++m_length;
    if(m_head==nullptr){
        m_head=m_end=new node(elem);
        return;
    }
    m_end->next=new node(elem);
    m_end=m_end->next;
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::pop_front(){
    if(m_head==nullptr)
        throw std::out_of_range("forward_list_base::pop_front: empty list!");
    --m_length;
    if(m_end==m_head){
        delete m_end;
        m_head=m_end=nullptr;
        return;
    }
    node *save=m_head->next;
    delete m_head;
    m_head=save;
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::push_front(const T &elem){
    ++m_length;
    if(m_head==nullptr){
        m_head=m_end=new node(elem);
        return;
    }
    node *tmp=new node(elem);
    tmp->next=m_head;
    m_head=tmp;
}

template <class T,class Node> T& rubbish::forward_list_base<T,Node>::front() const {return m_head->data;}

template <class T,class Node> T& rubbish::forward_list_base<T,Node>::back() const {return m_end->data;}

template <class T,class Node> typename rubbish::forward_list_base<T,Node>::self_type& rubbish::forward_list_base<T,Node>::operator=(const self_type &other) {
    this->~forward_list_base();
    m_length=other.m_length;
    if(other.empty()){
        m_head=m_end=nullptr;
        return *this;
    }
    node **ptr=&m_head;const node *optr=other.m_head;
    *ptr=new node(*optr); optr=optr->next;
    while(optr!=nullptr){
        (*ptr)->next=new node(*optr);
        ptr=&(*ptr)->next;
    }
    m_end=*ptr;
    return *this;
}

template <class T,class Node> rubbish::forward_list_base<T,Node>& rubbish::forward_list_base<T,Node>::operator=(self_type &&other) {
    this->~forward_list_base();
    m_head=other.m_head;
    m_end=other.m_end;
    m_length=other.m_length;
    other.m_head=other.m_end=nullptr;
    other.m_length=0;
    return *this;
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::reverse(){
    if(m_head==nullptr||m_head->next==nullptr)
        return;
    m_end=m_head;
    node *nhead=nullptr;
    while(m_head!=nullptr){
        node *p=m_head->next;
        m_head->next=nhead;
        nhead=m_head;
        m_head=p;
    }
    m_head=nhead;
}

template <class T,class Node> void rubbish::forward_list_base<T,Node>::remove_after(iterator it){
    node const *_it=it.get();
    if(_it==nullptr||_it->next==nullptr)
        return;
    node *save=_it->next->next;
    delete _it->next;
    _it->next=save;
    m_length--;
}

template <class T,class Node> typename rubbish::forward_list_base<T,Node>::iterator rubbish::forward_list_base<T,Node>::begin() {return iterator(m_head);}

template <class T,class Node> typename rubbish::forward_list_base<T,Node>::iterator rubbish::forward_list_base<T,Node>::end() {return iterator(nullptr);}

template <class T,class Node> typename rubbish::forward_list_base<T,Node>::const_iterator rubbish::forward_list_base<T,Node>::cbegin() const {return const_iterator(const_cast<forward_list_base<T,Node>*>(this)->begin());}

template <class T,class Node> typename rubbish::forward_list_base<T,Node>::const_iterator rubbish::forward_list_base<T,Node>::cend() const {return const_iterator(const_cast<forward_list_base<T,Node>*>(this)->end());}
