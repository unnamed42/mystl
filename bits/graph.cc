template <class T> rubbish::graph<T>::graph(bool dir):nodes(),directed(dir){}

template <class T> rubbish::graph<T>::graph(const rubbish::graph<T> &g){
    _index_t size=g.nodes.size();
    for(_index_t i=0;i<size;i++){
        nodes.push_back(new vex_node(g.nodes[i]));
        arc_node **ptr=&nodes[i].next,*ptr_g=g.nodes[i].next;
        while(ptr_g!=nullptr){
            *ptr=new arc_node(ptr_g->data);
            ptr=&(*ptr)->next;ptr_g=ptr_g->next;
        }
    }
    directed=g.directed;
}

template <class T> rubbish::graph<T>::graph(std::initializer_list<T> &&value,std::initializer_list< std::pair<index_t,index_t> > &&adjacency,bool _directed):nodes(),directed(_directed){
    auto size=value.size();
    if(size==0)
        return;
    for(auto &&i:value)
        nodes.push_back(new vex_node(i));
    for(auto &&i:adjacency){
        if(i.first>=size||i.second>=size)
            throw std::runtime_error("graph::constructor: adjacency list out of range");
        bind(i.first,i.second);
    }
}

template <class T> rubbish::graph<T>::~graph(){
    for(auto &_node:nodes){
        arc_node *p=_node->next;
        while(p!=nullptr){
            arc_node *save=p->next;
            delete p;
            p=save;
        }
        delete _node;
    }
}

template <class T> void rubbish::graph<T>::append(const T &data){ nodes.push_back(new vex_node(data)); }

template <class T> void rubbish::graph<T>::bind(index_t vex1,index_t vex2){
    auto make_bind=[this](_index_t _vex1,_index_t _vex2){
        vex_node *p=nodes[_vex1];arc_node *ptr=new arc_node(_vex2);
        ptr->next=p->next;
        p->next=ptr;
    };
    make_bind(vex1,vex2);
    if(!directed)
        make_bind(vex2,vex1);
}

template <class T> bool rubbish::graph<T>::empty() const {return nodes.empty();}

template <class T> bool rubbish::graph<T>::is_directed() const {return directed;}

template <class T> T& rubbish::graph<T>::operator[](index_t i){return nodes[i]->data;}

template <class T> typename rubbish::graph<T>::dfs_iterator rubbish::graph<T>::begin(){ 
    if(nodes.empty())
        return dfs_iterator(-1);
    auto s=new std::deque<_index_t>;
    for(arc_node *ptr = nodes[0]->next; ptr != nullptr; ptr = ptr->next)
        s->push_back(ptr->data);
    return dfs_iterator(0,&nodes,s);
}

template <class T> typename rubbish::graph<T>::dfs_iterator rubbish::graph<T>::end(){ return dfs_iterator(-1); }

template <class T> typename rubbish::graph<T>::bfs_iterator rubbish::graph<T>::bfs_begin(){
    if(nodes.empty())
        return bfs_iterator(-1);
    auto q=new std::deque<_index_t>;
    for(arc_node *ptr = nodes[0]->next; ptr != nullptr; ptr = ptr->next)
        q->push_back(ptr->data);
    return bfs_iterator(0,&nodes,q);
}

template <class T> typename rubbish::graph<T>::bfs_iterator rubbish::graph<T>::bfs_end(){ return bfs_iterator(-1); }

template <class T> typename rubbish::graph<T>::topo_iterator rubbish::graph<T>::topo_begin(){
    if(!directed||nodes.empty())
        return topo_iterator(-1);
    auto size=nodes.size();
    long *indegree=new long[size](),stack=-1;
    // calculate in-degree
    for(auto ptr:nodes){
        for(arc_node *_ptr=ptr->next;_ptr!=nullptr;_ptr=_ptr->next)
            indegree[_ptr->data]++;
    }
    for(index_t i=0;i<size;i++){
        if(indegree[i]==0){
            indegree[i]=stack;
            stack=i; // stack push
        }
    }
    // cannot be sorted
    if(stack==-1)
        return topo_iterator(-1);
    else{
        long save=stack; // stack top
        stack=indegree[stack]; // stack pop
        return topo_iterator(save,&nodes,0,stack,indegree);
    }
}

template <class T> typename rubbish::graph<T>::topo_iterator rubbish::graph<T>::topo_end(){ return topo_iterator(-1); }


// class rubbish::graph<T>::iterator_base
template <class T> rubbish::graph<T>::iterator_base::iterator_base(_index_t _index,std::vector<data_type> *_nodes):index(_index),nodes(_nodes){}

template <class T> typename rubbish::graph<T>::iterator_base::reference rubbish::graph<T>::iterator_base::operator*() const {return nodes->at(index)->data;}

template <class T> typename rubbish::graph<T>::_index_t rubbish::graph<T>::iterator_base::get() const {return index;}

template <class T> bool rubbish::graph<T>::iterator_base::operator==(const self_type &other) const {return index==other.index && nodes==other.nodes;}

template <class T> bool rubbish::graph<T>::iterator_base::operator!=(const self_type &other) const {return index!=other.index && nodes!=other.nodes;}

//class rubbish::graph<T>::dfs_iterator
template <class T> rubbish::graph<T>::dfs_iterator::dfs_iterator(_index_t _index,std::vector<data_type> *_nodes,std::deque<_index_t> *_s):iterator_base(_index,_nodes),component(_index),visited(nullptr),s(_s){
    if(_index!=-1){
        visited=std::shared_ptr<bool>(new bool[nodes->size()](),std::default_delete<bool[]>()); // set all to false, not sure if this works in all conditions
        visited.get()[_index]=true;
        if(_s==nullptr)
            s=std::shared_ptr<std::deque<_index_t>>(new std::deque<_index_t>);
    }
}

template <class T> typename rubbish::graph<T>::dfs_iterator::self_type& rubbish::graph<T>::dfs_iterator::operator++(){
    if(nodes==nullptr||s==nullptr||nodes->size()==0){
        index=-1;
        return *this;
    }
    if(index_t(component)<nodes->size())
        s->push_back(component);
    else{
        index=-1;
        return *this;
    }
    bool changed=false; // so ugly implemented
    while(!s->empty()) {
        _index_t v = s->back();
        s->pop_back();
        if(!(visited.get()[v])) {
            visited.get()[v] = true;
            index=v;changed=true;
            for(arc_node *ptr = nodes->at(v)->next; ptr != nullptr; ptr = ptr->next)
                if(!visited.get()[ptr->data])
                    s->push_back(ptr->data);
            break;
        }
    }
    if(!changed){
        ++component;
        this->operator++();
    }
    return *this;
}

template <class T> typename rubbish::graph<T>::dfs_iterator::self_type rubbish::graph<T>::dfs_iterator::operator++(int){
    self_type i=*this;
    this->operator++();
    return i;
}

template <class T> typename rubbish::graph<T>::dfs_iterator::self_type& rubbish::graph<T>::dfs_iterator::operator=(const self_type &other){
    index=other.index;
    nodes=other.nodes;
    component=other.component;
    s=other.s;
    visited=other.visited;
    return *this;
}

// class rubbish::graph<T>::bfs_iterator
template <class T> rubbish::graph<T>::bfs_iterator::bfs_iterator(_index_t _index,std::vector<data_type>* _nodes,std::deque<_index_t> *_q):iterator_base(_index,_nodes),component(_index),visited(nullptr),q(_q){
    if(_index!=-1){
        visited=std::shared_ptr<bool>(new bool[nodes->size()](),std::default_delete<bool[]>()); // set all to false, not sure if this works in all conditions
        visited.get()[_index]=true;
        if(_q==nullptr)
            q=std::shared_ptr<std::deque<_index_t>>(new std::deque<_index_t>);
    }
}

template <class T> typename rubbish::graph<T>::bfs_iterator::self_type& rubbish::graph<T>::bfs_iterator::operator++(){
    if(nodes==nullptr||q==nullptr||nodes->size()==0){
        index=-1;
        return *this;
    }
    if(index_t(component)<nodes->size())
        q->push_back(component);
    else{
        index=-1;
        return *this;
    }
    bool changed=false;
    while(!q->empty()) {
        _index_t v = q->front();
        q->pop_front();
        if(!visited.get()[v]) {
            visited.get()[v] = true;
            for(arc_node *ptr = nodes->at(v)->next; ptr != nullptr; ptr = ptr->next) {
                if(!visited.get()[ptr->data])
                    q->push_back(ptr->data);
            }
            index = v; changed = true; break;
        }
    }
    if(!changed){
        ++component;
        this->operator++();
    }
    return *this;
}

template <class T> typename rubbish::graph<T>::bfs_iterator::self_type rubbish::graph<T>::bfs_iterator::operator++(int){
    self_type i=*this;
    this->operator++();
    return i;
}

template <class T> typename rubbish::graph<T>::bfs_iterator::self_type& rubbish::graph<T>::bfs_iterator::operator=(const self_type &other){
    
    q=other.q;
    visited=other.visited;
    index=other.index;
    nodes=other.nodes;
    component=other.component;
    return *this;
}


// class rubbish::graph<T>::topo_iterator
template <class T> rubbish::graph<T>::topo_iterator::topo_iterator(_index_t _index,std::vector<data_type> *_nodes,std::size_t _count,long _stack,long *_indegree):iterator_base(_index,_nodes),stack(_stack),count(_count),indegree(){
    indegree=std::shared_ptr<long>(_indegree,std::default_delete<long[]>());
}

template <class T> typename rubbish::graph<T>::topo_iterator::self_type& rubbish::graph<T>::topo_iterator::operator++(){
    index=stack;
    if(stack==-1)
        return *this;
    stack=indegree.get()[stack];
    if((++count)>nodes->size())
        index=-1;       // Circle exists,cannot continue
    for(auto ptr=nodes->at(index)->next;ptr!=nullptr;ptr=ptr->next){
        if(--(indegree.get()[ptr->data])==0){
            indegree.get()[ptr->data]=stack;
            stack=ptr->data;
        }
    }
    return *this;
}

template <class T> typename rubbish::graph<T>::topo_iterator::self_type rubbish::graph<T>::topo_iterator::operator++(int){
    self_type i=*this;
    this->operator++();
    return i;
}

template <class T> typename rubbish::graph<T>::topo_iterator::self_type& rubbish::graph<T>::topo_iterator::operator=(const self_type &other){
    indegree=other.indegree;
    index=other.index;
    nodes=other.nodes;
    stack=other.stack;
    return *this;
}
