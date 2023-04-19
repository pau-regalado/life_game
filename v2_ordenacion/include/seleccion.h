#ifndef _SELECCION_
#define _SELECCION_

#include "SortMethod.h"

template <class Key>
class SeleccionMethod: public SortMethod<Key>{
  public:
    SeleccionMethod(std::vector<Key>* v, unsigned size): SortMethod<Key>{ v, size} {}
    void Sort() {
      seleccion(this->seq_, this->size_);
    }
    void seleccionar(std::vector<Key>* vector, int size){
        for(int i = 0; i < vector->size() - 1; i++){
          int min = i;
          for(int j = i + 1; j < vector->size(); j++){
            if (vector->at(j) < vector->at(min)){
              min = j;
            }
          }
          swap(vector,min,i);
          mostrar_v(vector);
        }
    }

    void seleccion(std::vector<Key>* vector,int size){
      for(int i = 0; i < size - 1; i++){
        seleccionar(vector, i);
        mostrar_v(vector);
      }
    }
};

#endif