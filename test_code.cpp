#include "all.h"
#include <algorithm>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <string>
#include <random>

#define MESSAGE(msg) std::cout<<msg<<std::endl

using namespace rubbish;

void continuous_container_test();
void vector_test();
void forward_list_test();
void list_test();
void binary_tree_test();
void bsearch_tree_test();
void avl_tree_test();
void map_test();
void graph_test();

int main(){
    continuous_container_test();
    vector_test();
    forward_list_test();
    list_test();
    binary_tree_test();
    bsearch_tree_test();
    avl_tree_test();
    map_test();
    graph_test();
    MESSAGE("\nAll tests are done.");
    return 0;
}

void forward_list_test(){
    struct test{
        int data;
        test(int n=0):data(n){}
        void increment(){data++;}
    };
    
    MESSAGE("forward_list tests begin. Involving push_back() and iterators.");
    forward_list<test> l;
    MESSAGE("forward_list default initialized.");
    for(int i=0;i<10;i++)
        l.push_back(test(i));
    MESSAGE("push_back() 0-9 successful.");
    for(auto &i:l)
        i.increment();
    MESSAGE("range based for loop(i.e. iterators) successful. Elements:");
    std::for_each(l.begin(),l.end(),[](test &t){std::cout<<t.data<<" ";});
    MESSAGE("\nforward_list tests end.\n");
}

void list_test(){
    MESSAGE("list tests begin. Involving push_back(),sort() and iterators.");
    list<int> list;
    MESSAGE("list default initialized.");
    // Random integer generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,100);
    for(auto i=0;i<10;++i)
        list.push_back(dist(gen));
    MESSAGE("push_back() 10 ints successful.");
    MESSAGE("range based for loop(i.e. iterators) begins:");
    for(auto &i:list)
        std::cout<<i<<" ";
    MESSAGE("\nsorted elements:");
    list.sort();
    for(auto &i:list)
        std::cout<<i<<" ";
    MESSAGE("\nReverse iterator tests, trying to output elements:");
    for(auto it=list.rbegin();it!=list.rend();++it)
        std::cout<<*it<<" ";
    MESSAGE("\nlist tests end.\n");
}

void graph_test(){
    MESSAGE("graph tests begin. Involving iterators only.");
    graph<int> a({0,1,2,3,4,5,6},{{0,1},{0,2},{1,3},{2,3},{2,4},{3,5},{4,5}},true);
    MESSAGE("graph direct initialized with an adjacency list successful.");
    std::vector<int> sv;
    struct op{
        std::vector<int> *p;
        void operator()(int c){
            if(p==nullptr)
                std::cout<<c;
            else
                p->push_back(c);
        }
        explicit op(std::vector<int> *_p=nullptr):p(_p){}
    };
    MESSAGE("depth first iterators tests, trying to output elements:");
    for(auto &i:a)
        std::cout<<i<<" ";
    MESSAGE("\nbreadth first iterators tests, trying to output elements:");
    for(auto i=a.bfs_begin();i!=a.bfs_end();++i)
        std::cout<<*i<<" ";
    MESSAGE("\ntopological iterators tests, trying to output elements:");
    for(auto i=a.topo_begin();i!=a.topo_end();++i)
        std::cout<<*i<<" ";
    MESSAGE("\ngraph tests end.\n");
}

void continuous_container_test(){
    MESSAGE("continuous_container tests begin. Involving iterators only.");
    continuous_container<int> cc(10,2);
    MESSAGE("continuous_container filled with 10 elements whose value is 2. Outputting:");
    for(auto &i:cc)
        std::cout<<i<<" ";
    MESSAGE("\ncontinuous_container tests end.\n");
}

void vector_test(){
    MESSAGE("vector tests begin. Involving iterators only.");
    vector<int> v{0,1,2,3,45};
    MESSAGE("vector direct initialized with an initializer list successful.");
    for(auto &i:v)
        std::cout<<i<<" ";
    MESSAGE("\nvector tests end.\n");
}

void avl_tree_test(){
    auto val=[](helper::avl_tree_node<int> *p) {return p==nullptr?-1:p->data;};
    MESSAGE("avl_tree tests begin. Involving insert(),erase() and iterators.");
    avl_tree<int> te({1,2,3,3,3,86,651,32,41,651,984,16,19,41,0});
    MESSAGE("avl_tree direct initialized with an initializer list successful. Outputting nodes in level order:");
    for(auto it=te.level_begin();it!=te.level_end();++it){
        auto &&ptr=it.get().front();
        std::cout<<"this:"<<val(ptr)<<" left:"<<val(ptr->left)<<" right:"<<val(ptr->right)<<" parent:"<<val(ptr->parent)<<std::endl;
    }
    MESSAGE("Outputting nodes in in-order:");
    for(auto &i:te)
        std::cout<<i<<" ";
    te.erase(3);
    MESSAGE("\nerase(3) executed:");
    for(auto &i:te)
        std::cout<<i<<" ";
    MESSAGE("insert(195) and tests with the returned iterator:");
    auto x=te.insert(195);
    std::cout<<(x!=te.end()?*x:0)<<std::endl;
    MESSAGE("Outputting nodes in in-order again:");
    for(auto &i:te)
        std::cout<<i<<" ";
    MESSAGE("\navl_tree tests end.\n");
}

void bsearch_tree_test(){
    MESSAGE("bsearch_tree tests begin. Involving iterators only.");
    bsearch_tree<int> tree({1,5,7,9,5,25,0,1,9,4,1});
    MESSAGE("bsearch_tree direct initialized with an initializer list successful. Outputting nodes in in-order:");
    for(auto &i:tree)
        std::cout<<i<<" ";
    MESSAGE("\nOutputting nodes in level order:");
    for(auto it=tree.level_begin();it!=tree.level_end();++it)
        std::cout<<(*it)<<" ";
    MESSAGE("\nbsearch_tree tests end.\n");
}

void binary_tree_test(){
    MESSAGE("binary_tree tests begin. Involving iterators only.");
    binary_tree<int> tree({1,2,3,4,5,6,7,8,9,10},0);
    MESSAGE("binary_tree initialized with an level order serialization successful. Outputting in pre-order:");
    for(auto it=tree.preorder_begin();it!=tree.preorder_end();++it)
        std::cout<<(*it)<<" ";
    MESSAGE("\nOutputting nodes in in-order:");
    for(auto it=tree.inorder_begin();it!=tree.inorder_end();++it)
        std::cout<<(*it)<<" ";
    MESSAGE("\nOutputting nodes in post-order:");
    for(auto it=tree.postorder_begin();it!=tree.postorder_end();++it)
        std::cout<<(*it)<<" ";
    MESSAGE("\nOutputting nodes in level order:");
    for(auto it=tree.level_begin();it!=tree.level_end();++it)
        std::cout<<(*it)<<" ";
    binary_tree<int> treea({1,2,4,8,9,5,10,3,6,7},{8,4,9,2,10,5,1,6,3,7});
    MESSAGE("\nAnother binary_tree initialized with pre-order and in-order serialization successful. Outputting in level order:");
    for(auto it=treea.level_begin();it!=treea.level_end();++it)
        std::cout<<(*it)<<" ";
    MESSAGE("\nbinary_tree tests end.\n");
}

void map_test(){
    MESSAGE("map tests begin. Involving find(),erase(),iterators and pair utility.");
    const std::string str("abc");
    map<std::string,int> m={{"abc",2568},{"ffg",45},{"eat",445}};
    MESSAGE("map initialized with an initializer list successful.\nThe list is:{\"abc\",2568},{\"ffg\",45},{\"eat\",445}\nFinding \"abc\" in map:");
    std::cout<<m.find(std::string("abc"))->second<<" "<<std::endl;
    MESSAGE("Add 554 to \"abc\"'s corresponding value successful. Reprinting:");
    m.find(std::string(str))->second+=554;
    std::cout<<m.find(std::string(str))->second<<std::endl;
    m.erase(std::string("ffg"));
    MESSAGE("\"ffg\" deleted. Outputting nodes:");
    for(auto &i:m)
        std::cout<<i.first<<" "<<i.second<<std::endl;
    MESSAGE("map tests end.\n");
}

#undef MESSAGE
