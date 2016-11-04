#ifndef __CS235_SORTED_VECTOR_H_
#define __CS235_SORTED_VECTOR_H_

#include <iostream>
#include <vector>

/*
 This class implements a sorted vector, using the STL
 vector as its underlying container.
 This class' condition of "sorted-ness" implies that any
 literal or object type (T) that this class contains must
 have the ability to be "compared." This will manifest in
 the form of a call to operator<. Therefore, the object type
 (T) must at least implement operator<.
 HOWEVER, if this class will hold POINTERS to OBJECTS, you
 must go one step further. You must create a "comparator"
 struct/class that implements the operator() function. Inside
 of this function, you must return the result of a "less than"
 comparison (simply, *obj1 < *obj2!). Then, you must supply
 this comparator struct as the second template parameter.
 */
template<class T, class Comparator = std::less<T>>
class SortedVector {
public:
    
    SortedVector() { vec.reserve(50); }
    virtual ~SortedVector() {};
    
    // O(1) operations
    unsigned int capacity() const { return (unsigned int) vec.capacity(); }
    unsigned int size() const { return (unsigned int) vec.size(); }
    bool empty() const { return vec.empty(); }
    
    T& at(unsigned int pos) { return vec.at(pos); }
    T& front() { return vec.front(); }
    T& back() { return vec.back(); }
    const T& at(unsigned int pos) const { return vec.at(pos); }
    const T& front() const { return vec.front(); }
    const T& back() const { return vec.back(); }
    
    T& pop_back() { T& data = back(); vec.pop_back(); return data; }
    
    // O(n) operations
    void clear() { vec.clear(); }
    void display() const;
    
    // Altered insert function to also return position inserted into.
    unsigned int insert(const T& data);
    T& remove(unsigned int pos) { auto it = vec.begin(); std::advance(it,pos); T& data = *it; vec.erase(it); return data; }
    
    std::vector<T> toVector() const;
    
private:
    
    std::vector<T> vec;
    
};

#include "SortedVector.cpp"

#endif
