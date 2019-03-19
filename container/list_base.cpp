#include "list_base.hpp"

using namespace rubbish;

// class list_base {
// protected:
//     struct list_node {
//         list_node *prev, *next;
//         list_node() : prev(nullptr), next(nullptr) {}
//     };
// protected:
//     list_node *head = nullptr;
//     list_node *tail = nullptr;
//     size_t     len  = 0;
// public:
//     list_base(const list_base &);
//     list_base(list_base &&) noexcept;
//
//     size_t size() const noexcept;
//
//     void reverse();
//     void clear();
//
//     void swap(list_base &);
//
//     void push_back(list_node*);
//     void pop_back();
// protected:
//     void erase(list_node *);
// };


list_base::list_base(const list_base &other) {
    if(other.empty()) return;

}
