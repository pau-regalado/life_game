#ifndef _INCR_DEC_
#define _INCR_DEC_

#include "commons.h"

template <typename Clave>
void sort(std::vector<Clave>* vector, int delta, int size){
  Clave x; 
  int j;
  std::cout << " delta = " << delta << std::endl;
  for(int i = delta; i < size; i++){
    x = vector->at(i);
    j = i;
    while ((j >= delta) && (x < vector->at(j - delta))){  
      vector->at(j) = vector->at(j - delta);
      j = j - delta;
    }
    vector->at(j) = x;
    mostrar_v(vector);
  }
}

template <typename Clave>
void incr_dec(std::vector<Clave>* vector, float alpha, int size){
  int delta = size;
  while(delta > 1){
    delta = int(delta * alpha);
    if (delta < 1) {
      delta = 1;
    }
    sort(vector, delta, size);
  }
}

#endif