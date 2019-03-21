#ifndef ALGORITHM_COMPARE
#define ALGORITHM_COMPARE

namespace stl {

template <class InputIt, class SentinelIt>
auto compare(InputIt first1, SentinelIt last1, InputIt first2, SentinelIt last2) {
    while(first1 != last1 && first2 != last2) {
        if(*first1 != *first2) break;
        ++first1; ++first2;
    }
    return *first1 - *first2;
}

template <class InputIt, class SentinelIt, class Equal>
auto compare(InputIt first1, SentinelIt last1, InputIt first2, SentinelIt last2, Equal &&eq) {
    while(first1 != last1 && first2 != last2) {
        if(!eq(*first1, *first2)) break;
        ++first1; ++first2;
    }
    return *first1 - *first2;
}

} // namespace stl

#endif // ALGORITHM_COMPARE
