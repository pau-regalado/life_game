#ifndef _SELECCION_
#define _SELECCION_

#include "commons.h"


template <typename Clave>
void seleccionar(std::vector<Clave>* vector, int size){
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

template <typename Clave>
void seleccion(std::vector<Clave>* vector,int size){
  for(int i = 0; i < size - 1; i++){
    seleccionar(vector, i);
    mostrar_v(vector);
  }
}

#endif