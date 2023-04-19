#ifndef _METODOS_
#define _METODOS_

#include <iostream>
#include <vector>
#include <climits>

//Recibe un puntero al vector a ordenar y su tamaño y lo ordena.
template <class Clave>
void mostrar_v(std::vector<Clave>* v){
  std::cout << "< ";
  for (int i = 0; i < v->size(); ++i)
    std::cout << v->at(i) << " ";
  std::cout << ">" << std::endl;
}

template <class Clave>
void swap(std::vector<Clave>* vector, int x, int y){
  Clave aux = vector->at(x);
  vector->at(x) = vector->at(y);
  vector->at(y) = aux; 
}

#endif