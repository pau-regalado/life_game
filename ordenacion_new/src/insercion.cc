#include "../include/insercion.h"

template <class Clave>
void insercion(std::vector<Clave>* vector, unsigned size) {

  int j;
  for (int i = 1; i < size; i++){
    j = i - 1;
    Clave x = vector->at(i);
    while ((j >= 0) && (x < vector->at(j))){
      //std::cout << "intercambio el " << vector->at(j) << " en la pos " << j;
      //std::cout << " por el " << vector->at(j+1) << " en la pos " << j+1 << std::endl;
      vector->at(j+1) = vector->at(j);
      j--;
    }
    vector->at(j+1) = x;

    mostrar_v(vector);
  }
}
