#ifndef _INSERCION_
#define _INSERCION_

#include "SortMethod.h"

template <class Key>
class InsercionMethod: public SortMethod<Key>{
  public:
    InsercionMethod(std::vector<Key>* v, unsigned size): SortMethod<Key>{ v, size} {}
    void Sort() {
      insercion(this->seq_, this->size_);
    }
    void insercion(std::vector<Key>* vector, unsigned size) {
      int j;
      for (int i = 1; i < size; i++){
        j = i - 1;
        Key x = vector->at(i);
        while ((j >= 0) && (x < vector->at(j))){
          vector->at(j+1) = vector->at(j);
          j--;
        }
        vector->at(j+1) = x;

        // mostrar_v(vector);
      }
    }
};

#endif