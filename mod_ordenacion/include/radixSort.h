#ifndef _RADIXSORT_
#define _RADIXSORT_

#include <math.h>
#include "SortMethod.h"
const int kDigits = 4;

template <class Key>
class RadixSortMethod: public SortMethod<Key>{
  public:
  RadixSortMethod(std::vector<Key>* v, unsigned size): SortMethod<Key>{ v, size} {}
    void Sort() {
      radixSort(this->seq_, this->size_);
    }

  void radixSort(std::vector<Key>* vector, int size){
    for (int i = 0; i < kDigits; i++) {
      std::vector<std::vector<int>> cubetas;
      cubetas.resize(10);
      
      for (int j = 0; j < size; j++) {
        cubetas[(vector->at(j) / int(pow(10, i))) % 10].push_back(vector->at(j));
      }
      int index = 0;
      for (int k = 0; k <cubetas.size(); k++) {
        for (int l = 0; l < cubetas[k].size(); l++) {
          vector->at(index++) = cubetas[k][l];
        }
      }
      std::cout << "Ordenacion por " << i + 1 << "º digito" << std::endl;
      mostrar_v(vector);
    }
  }

};


#endif