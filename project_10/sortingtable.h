//
//  sortingtable.h
//  project10-mac
//
//  Created by florrie on 2020/12/1.
//  Copyright © 2020 Florrie. All rights reserved.
//

#ifndef sortingtable_h
#define sortingtable_h

#include <iostream>
using namespace std;

template <typename T>
class Element {
    friend class Sort;
public:
    T key;
    Element<T>&operator = (Element<T> &x) {key = x.key;return this;}
    bool operator == (Element<T> &x) {return key == x.key;}
    bool operator <= (Element<T> &x) {return key <= x.key;}
    bool operator >= (Element<T> &x) {return key >= x.key;}
    bool operator < (Element<T> &x) {return key < x.key;}
    bool operator > (Element<T> &x) {return key > x.key;}
};

template <typename T>
class SortingTable {
private:
    Element<T> *vector;
    int size;
public:
    SortingTable(int sz = 0){size = sz;vector = new T[size];}
    void swap(Element<T> &x,Element<T> &y){Element<T> temp = x;x = y;y = temp;}
    Element<T> &operator[](int i) {return vector[i];}
};


#endif /* sortingtable_h */
