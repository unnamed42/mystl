#ifndef __RUBBISH_GRAPH__
#define __RUBBISH_GRAPH__

#include <deque>
#include <vector>
#include <memory> // std::shared_ptr
#include <utility> // std::pair, std::forward
#include <stdexcept>
#include <initializer_list> // std::initializer_list
#include "iterator.hpp"
#include "type_traits/basic_traits.hpp"

namespace rubbish{
    
    template <class T> class graph{
        public:
            typedef std::size_t index_t;
            
            typedef long _index_t; // A type used to represent index of nodes, `-1` means "no such node". Used only by iterators.
            
            template <class U> struct node{
                typedef node<U> self_type;
                
                U data;
                node<index_t> *next;
                
                constexpr node():data(),next(nullptr) {}
                explicit node(const U &e):data(e),next(nullptr) {}
                explicit node(U &&e):data(std::move(e)),next(nullptr) {}
                node(const self_type &o):data(o.data),next(o.next) {}
                node(self_type &&o):data(std::move(o.data)),next(o.next) {}
                
                self_type& operator=(const self_type &o) {data=o.data;next=o.next;return *this;}
                self_type& operator=(self_type &&o) {data=std::move(o.data);next=o.next;return *this;}
            };
            
            typedef node<T> vex_node;
            typedef node<index_t> arc_node;
            
            class iterator_base:public iterator<std::forward_iterator_tag,T>{
                private:
                    typedef iterator<std::forward_iterator_tag,T> base_class;
                public:
                    typedef typename base_class::reference reference;
                    typedef typename base_class::pointer   pointer;
                    
                    typedef iterator_base self_type;
                    typedef vex_node*     data_type;
                    
                    iterator_base(_index_t _index,std::vector<vex_node*>* =nullptr);
                    virtual ~iterator_base() {}
                    
                    reference operator*() const;
                    pointer operator->() const {return &operator*();}
                    _index_t get() const;
                    
                    bool operator==(const self_type &other) const;
                    bool operator!=(const self_type &other) const;
                protected:
                    _index_t index;
                    std::vector<vex_node*> *nodes;
            };
            
            class dfs_iterator: public iterator_base{
                public:
                    typedef dfs_iterator                      self_type;
                    typedef typename iterator_base::data_type data_type;
                    
                    explicit dfs_iterator(_index_t _index,std::vector<data_type>* =nullptr,std::deque<_index_t>* =nullptr);
                    
                    self_type& operator++();
                    self_type operator++(int);
                    self_type& operator=(const self_type &other);
                protected:
                    using iterator_base::index;
                    using iterator_base::nodes;
                    _index_t component; // Set `component` to iterate over isolated nodes.
                    std::shared_ptr<bool> visited;
                    std::shared_ptr<std::deque<_index_t>> s;//stack
            };
            
            class bfs_iterator: public iterator_base{
                public:
                    typedef bfs_iterator                      self_type;
                    typedef typename iterator_base::data_type data_type;
                    
                    explicit bfs_iterator(_index_t _index,std::vector<data_type>* =nullptr,std::deque<_index_t>* =nullptr);
                    
                    self_type& operator++();
                    self_type operator++(int);
                    self_type& operator=(const self_type &other);
                protected:
                    using iterator_base::index;
                    using iterator_base::nodes;
                    _index_t component;
                    std::shared_ptr<bool> visited;
                    std::shared_ptr<std::deque<_index_t>> q;//queue
            };
            
            class topo_iterator: public iterator_base{
                public:
                    typedef topo_iterator                     self_type;
                    typedef typename iterator_base::data_type data_type;
                    
                    explicit topo_iterator(_index_t _index,std::vector<data_type>* =nullptr,std::size_t count=0,long stack=-1,long *indegree=nullptr);
                    
                    self_type& operator++();
                    self_type operator++(int);
                    self_type& operator=(const self_type &other);
                protected:
                    using iterator_base::index;
                    using iterator_base::nodes;
                    long stack;
                    std::size_t count;
                    std::shared_ptr<long> indegree;
            };
            
            typedef dfs_iterator iterator;
            
        protected:
            std::vector<vex_node*> nodes;
            bool directed;
        public:
            // Construct an empty graph, by default it's undirected graph
            explicit graph(bool=false);
            
            // Copy-constructor
            graph(const graph<T> &g);
            
            // Construct from two given lists, one is value of nodes, one is relation between nodes. This funtion does no duplicate check
            graph(std::initializer_list<T>&&,std::initializer_list<std::pair<index_t,index_t>>&&,bool=false);
            
            // Destructor
            ~graph();
            
            // Append a node
            void append(const T &data);
            
            // Check if this graph holds no element
            bool empty() const;
            
            // Return if this is a directed graph
            bool is_directed() const;
            
            // Build connection between node `vex1` and `vex2`, there's difference if this graph is directed
            void bind(index_t vex1,index_t vex2);
            
            // Return referencet to the `i`-th node
            T& operator[](index_t i);
            
            // Iterator functions
            dfs_iterator begin();
            
            dfs_iterator end();
            
            bfs_iterator bfs_begin();
            
            bfs_iterator bfs_end();
            
            topo_iterator topo_begin();
            
            topo_iterator topo_end();
    };
} // namespace rubbish

#include "graph.cc"

#endif // __RUBBISH_GRAPH__
