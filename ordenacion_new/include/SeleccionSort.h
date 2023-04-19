#ifndef __SELECCIONSORT__
#define __SELECCIONSORT__

#include <iostream>
#include <vector>
#include <climits>

#include "SortMethod.h"

template<class Key>
class SeleccionSort: public SortMethod<Key> {
  public:
    virtual void Sort();
    void seleccionarSort();
};

#endif