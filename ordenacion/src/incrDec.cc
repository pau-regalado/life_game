#include "../include/incrDec.h"

template <class Clave>
void incr_dec(std::vector<Clave>* vector, float alpha, int size){
  int delta = int(size*alpha);
  while(delta >= 1){
    std::cout << " delta = " << delta << std::endl;
    sort(vector,delta,size);
    delta = int(delta*alpha);
  }
}

template <class Clave>
void sort(std::vector<Clave>* vector, int delta, int size){
  Clave x; 
  int j;
  std::cout << " delta = " << delta << std::endl;
  for(int i = delta; i < size; ++i){
    x = vector->at(i);
    j = i;
    while ((j >= delta) && (x < vector->at(j-delta))){  
      vector->at(j) = vector->at(j-delta);
      j = j - delta;
    }
    vector->at(j) = x;
    mostrar_v(vector);
  }
}