#ifndef MEMORY_SHARED_PTR
#define MEMORY_SHARED_PTR

#include "def.hpp"
#include "meta/ref.hpp"

namespace rubbish {

template <class T>
struct default_deleter {
    void operator()(T *p) { delete p; }
};

template <class T>
struct default_deleter<T[]> {
    void operator()(T *p) { delete[] p; }
};

template <class T, class Deleter = default_deleter<T>>
class shared_ptr {
    static_assert(!is_reference_v<T>, "T cannot be a reference type");

    using type   = remove_extent_t<T>;
    using self_t = shared_ptr<T, Deleter>;
private:
    struct block_t {
        void  *p;
        size_t count;
    };
private:
    block_t *m_blk;
public:
    shared_ptr(T *p = nullptr) {
        if(p) m_blk = new block_t{p, 1};
    }

    template <class P>
    shared_ptr(shared_ptr<P> &other) {
        m_blk = other.m_blk;
        if(m_blk) ++m_blk->count;
    }



};

} // namespace rubbish

#endif // MEMORY_SHARED_PTR
