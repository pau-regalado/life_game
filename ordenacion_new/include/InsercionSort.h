#ifndef __INSERCIONSORT__
#define __INSERCIONSORT__

#include <iostream>
#include <vector>
#include <climits>

#include "SortMethod.h"

template<class Key>
class InsercionSort: public SortMethod<Key> {
  public:
    InsercionSort(std::vector<Key>* v, unsigned size): SortMethod<Key>(v, size){}
    virtual void Sort();
};

#endif