#ifndef _QUICKSORT_
#define _QUICKSORT_

#include "commons.h"

template <typename Clave>
void quicksort(std::vector<Clave>* vector, unsigned ini, unsigned fin){
  int i = ini, f = fin;
  int pivote = vector->at((i+f)/2);
  std::cout << "PIV " << pivote << std::endl;

  while (i <= f){ 
    while (vector->at(i) < pivote){ i++;}
    while (vector->at(f) > pivote){ f--;}

    if (i <= f){
      swap(vector,i,f);
      i++;
      f--;
    }
    //mostrar_v(vector);
  }

  if (i < 0) {
    i = 0;
  }
  if (f >= vector->size()) {
    f = vector->size() - 1;
  }
  std::cout << "i = " << i << " f = " << f << std::endl;

  if (ini < f){
    quicksort(vector,ini,f);
  }

  if (i < fin){
    quicksort(vector, i, fin);
  }

}

#endif