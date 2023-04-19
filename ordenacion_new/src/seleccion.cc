#include "../include/seleccion.h"

template <typename Clave>
void seleccionar(std::vector<Clave>* vector, int size){
    for(int i = 0; i < size; i++){
      int min = i;
      for(int j = i+1; j <= size; j++){
        if (vector->at(j) < vector->at(min)){
          min = j;
        }
      swap(vector,min,i);
      }
    }
}

template <typename Clave>
void seleccion(std::vector<Clave>* vector,int size){
  for(int i = 0; i < size; i++){
    seleccionar(vector,i);
    mostrar_v(vector);
  }
}