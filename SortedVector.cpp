#ifndef __CS235_SORTED_VECTOR_CPP_
#define __CS235_SORTED_VECTOR_CPP_

#include "SortedVector.h"

template<class T, class Comparator>
void SortedVector<T, Comparator>::display() const
{
    if (empty()) {
        std::cout << "(empty)" << std::endl;
        return;
    }
    for (int i = 0; i < size()-1; i++) {
        std::cout << vec[i] << ", ";
    }
    std::cout << vec[size()-1] << std::endl;
}

// Altered insert function to also return position inserted into.
template<class T, class Comparator>
unsigned int SortedVector<T, Comparator>::insert(const T& data)
{
    if (empty()) {
        vec.push_back(data);
        return 0;
    }
    
    // Temporary use of O(n) search algorithm to handle lower_bound issues
    Comparator comparator;
    int index = vec.size();
    for(unsigned int i = 0; i < vec.size(); ++i) {
        if(comparator(vec[i], data)) {
            continue;
        }
        else {
            index = i;
            break;
        }
    }
    
    vec.insert(vec.begin()+index, data);
    return index;
}

template<class T, class Comparator>
std::vector<T> SortedVector<T, Comparator>::toVector() const
{
    std::vector<T> outVec;
    for(unsigned int i = 0; i < vec.size(); ++i) {
        outVec.push_back(vec[i]);
    }
    return outVec;
}

#endif
