#include "../include/quickSort.h"

template <class Clave>
void quicksort(std::vector<Clave>* vector, unsigned ini, unsigned fin){
  int i = ini, f = fin;
  int pivote = vector->at((i+f)/2);

  //std::cout << "ini = " << ini << " fin = " << fin << " pivote = " << pivote << std::endl;
  while (i <= f){ 
    while (vector->at(i) < pivote){ i++;}
    while (vector->at(f) > pivote){ f--;}

    if (i <= f){
      swap(vector,i,f);
      //std::cout << "intercambio " << i << " por " << f << std::endl;
      i++;
      f--;
    }
    mostrar_v(vector);
  }
  //std::cout << "antes de la llamada recursiva" << std::endl;

  if (ini < f){
    quicksort(vector,ini,f);
  }

  if (i < fin){
    quicksort(vector,i,fin);
  }

}

