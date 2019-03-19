namespace rubbish{
    namespace helper{
        
        // I don't know how to maintain `prev` relationship in one run
        // TODO: Improve this algorithm
        template <class Node> Node* list_merge(Node *h1,Node *h2){
            if(h1==h2)
                return h1;
            Node *head=nullptr,**ptr=&head;
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
            head->prev=nullptr;
            return head;
        }
        
        template <class Node> Node* list_merge_sort(Node *head){
            if(head==nullptr||head->next==nullptr)
                return head;
            if(head->next->next==nullptr){
                Node *node=head->next;
                if(node->data<head->data){
                    node->next=head;
                    head->prev=node;
                    head->next=node->prev=nullptr;
                    head=node;
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
            slow->next->prev=nullptr;
            fast=list_merge_sort<Node>(slow->next);
            slow->next=nullptr;
            return list_merge<Node>(list_merge_sort<Node>(head),fast);
        }
    
    } // namespace helper
} // namespace rubbish

template <class T,class Node> constexpr rubbish::list_base<T,Node>::list_base():m_head(nullptr),m_end(nullptr),m_length(0){}

template <class T,class Node> rubbish::list_base<T,Node>::list_base(std::size_t len,const T &value):m_head(nullptr),m_end(nullptr),m_length(len){
    if(len==0)
        return;
    node dummy;
    node *ptr=&dummy;
    for(;len>0;--len){
        ptr->next=new node(value);
        ptr->next->prev=ptr;
        ptr=ptr->next;
    }
    m_end=ptr;m_head=dummy.next;
    m_head->prev=nullptr;
}

template <class T,class Node> rubbish::list_base<T,Node>::list_base(std::initializer_list<T> &&l):m_head(nullptr),m_end(nullptr),m_length(0){
    if(l.size()==0)
        return;
    auto it=l.begin();
    m_head=m_end=new node(*(it++));
    for(;it!=l.end();++it){
        m_end->next=new node(*it);
        m_end->next->prev=m_end;
        m_end=m_end->next;
    }
}

template <class T,class Node> rubbish::list_base<T,Node>::list_base(const self_type &o):m_head(nullptr),m_end(nullptr),m_length(o.m_length){
    if(o.empty())
        return;
    const node *optr=o.m_head;
    // Pointers in the newed node must all be nullptr, otherwise assign manually
    m_head=m_end=new node(*optr);
    optr=optr->next;
    while(optr!=nullptr){
        m_end->next=new node(*optr);
        m_end->next->prev=m_end;
        m_end=m_end->next;
        optr=optr->next;
    }
}

template <class T,class Node> rubbish::list_base<T,Node>::list_base(self_type &&o):m_head(o.m_head),m_end(o.m_end),m_length(o.m_length) {o.m_head=o.m_end=nullptr;o.m_length=0;}

template <class T,class Node> rubbish::list_base<T,Node>::~list_base(){
    node *save;
    while(m_head!=nullptr){
        save=m_head->next;
        delete m_head;
        m_head=save;
    }
}

template <class T,class Node> std::size_t rubbish::list_base<T,Node>::size() const noexcept {return m_length;}

template <class T,class Node> bool rubbish::list_base<T,Node>::empty() const {return m_head==nullptr;}

template <class T,class Node> void rubbish::list_base<T,Node>::reverse(){
    if(m_head==nullptr||m_head->next==nullptr)
        return;
    m_end=m_head;
    node *_node=m_head->next;
    while(_node->next!=nullptr){
        node *temp=_node->prev;
        _node->prev=_node->next;
        _node->next=temp;
        _node=_node->prev;
    }
    m_head=_node;
}

template <class T,class Node> void rubbish::list_base<T,Node>::sort() {
    if(m_head==nullptr||m_head->next==nullptr)
        return;
    m_head=helper::list_merge_sort(m_head);
    // Fix linkage and find m_end
    node *prev=m_head,*next=m_head->next;
    prev->prev=nullptr;
    while(next!=nullptr){
        next->prev=prev;
        prev=next;
        next=next->next;
    }
    m_end=prev;
}

template <class T,class Node> void rubbish::list_base<T,Node>::clear() {
    this->~list_base();
    m_head=m_end=nullptr;
    m_length=0;
}

template <class T,class Node> void rubbish::list_base<T,Node>::push_back(const T &elem){
    ++m_length;
    if(m_head==nullptr){
        m_head=m_end=new node(elem);
        return;
    }
    m_end->next=new node(elem);
    m_end->next->prev=m_end;
    m_end=m_end->next;
}

template <class T,class Node> void rubbish::list_base<T,Node>::pop_back(){
    if(m_end==nullptr)
        throw std::out_of_range("list_base::pop_back: empty list!");
    --m_length;
    if(m_end==m_head){
        delete m_end;
        m_head=m_end=nullptr;
        return;
    }
    node *save=m_end->prev;
    save->next=nullptr;
    delete m_end;
    m_end=save;
}

template <class T,class Node> void rubbish::list_base<T,Node>::pop_front(){
    if(m_head==nullptr)
        throw std::out_of_range("list_base::pop_back: empty list!");
    --m_length;
    if(m_end==m_head){
        delete m_end;
        m_head=m_end=nullptr;
        return;
    }
    node *save=m_head->next;
    save->prev=nullptr;
    delete m_head;
    m_head=save;
}

template <class T,class Node> void rubbish::list_base<T,Node>::push_front(const T &elem){
    ++m_length;
    if(m_head==nullptr){
        m_head=m_end=new node(elem);
        return;
    }
    node *tmp=new node(elem);
    tmp->next=m_head;
    m_head->prev=tmp;
    m_head=tmp;
}

template <class T,class Node> T& rubbish::list_base<T,Node>::front() const {return m_head->data;}

template <class T,class Node> T& rubbish::list_base<T,Node>::back() const {return m_end->data;}

template <class T,class Node> void rubbish::list_base<T,Node>::remove(iterator it){
    node *ptr=it.get();
    if(ptr==nullptr)
        return;
    --m_length;
    if(ptr==m_head && ptr==m_end){
        delete ptr;
        m_head=m_end=nullptr;
    } else if(ptr==m_head) {
        ptr=m_head->next;
        delete m_head;
        m_head=ptr;
    } else if(ptr==m_end) {
        ptr=m_end->prev;
        delete m_end;
        m_end=ptr;
    } else {
        ptr->next->prev=ptr->prev;
        ptr->prev->next=ptr->next;
        delete ptr;
    }
}

template <class T,class Node> typename rubbish::list_base<T,Node>::self_type& rubbish::list_base<T,Node>::operator=(const self_type &o) {
    this->~list_base();
    m_length=o.m_length;
    if(o.empty()){
        m_head=m_end=nullptr;
        return *this;
    }
    const node *optr=o.m_head;
    m_head=m_end=new node(*optr);
    optr=optr->next;
    while(optr!=nullptr){
        m_end->next=new node(*optr);
        m_end->next->prev=m_end;
        m_end=m_end->next;
        optr=optr->next;
    }
    return *this;
}

template <class T,class Node> typename rubbish::list_base<T,Node>::self_type& rubbish::list_base<T,Node>::operator=(self_type &&o) {
    this->~list_base();
    m_head=o.m_head;
    m_end=o.m_end;
    m_length=o.m_length;
    o.m_head=o.m_end=nullptr;
    o.m_length=0;
    return *this;
}

template <class T,class Node> typename rubbish::list_base<T,Node>::iterator rubbish::list_base<T,Node>::begin() {return iterator(m_head);}

template <class T,class Node> typename rubbish::list_base<T,Node>::iterator rubbish::list_base<T,Node>::end() {return iterator(nullptr);}

template <class T,class Node> typename rubbish::list_base<T,Node>::const_iterator rubbish::list_base<T,Node>::cbegin() const {return const_iterator(const_cast<list_base<T,Node>*>(this)->begin());}

template <class T,class Node> typename rubbish::list_base<T,Node>::const_iterator rubbish::list_base<T,Node>::cend() const {return const_iterator(const_cast<list_base<T,Node>*>(this)->end());}

template <class T,class Node> typename rubbish::list_base<T,Node>::reverse_iterator rubbish::list_base<T,Node>::rbegin() {return reverse_iterator(iterator(m_end));}

template <class T,class Node> typename rubbish::list_base<T,Node>::reverse_iterator rubbish::list_base<T,Node>::rend() {return reverse_iterator(end());}

template <class T,class Node> typename rubbish::list_base<T,Node>::const_reverse_iterator rubbish::list_base<T,Node>::crbegin() const {return const_reverse_iterator(const_cast<list_base<T,Node>*>(this)->rbegin());}

template <class T,class Node> typename rubbish::list_base<T,Node>::const_reverse_iterator rubbish::list_base<T,Node>::crend() const {return const_reverse_iterator(const_cast<list_base<T,Node>*>(this)->rend());}
