#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "../include/quickSort.h"
#include "../include/incrDec.h"
#include "../include/heapSort.h"
#include "../include/seleccion.h"

const int MAX_INT = 9999;
const int MIN_INT = 1000;

void show_menu(void){
  std::cout << "Método de ordenación: " << std::endl;
  std::cout << "q) Quicksort " << std::endl;
  std::cout << "d) Incrementos decrecientes" << std::endl;
  std::cout << "h) heapsort" << std::endl;
  std::cout << "s) Seleccion" << std::endl;
  std::cout << "k) quit" << std::endl;
  std::cout << "Opción: ";
}

template <typename Clave>
void fillRandVector (std::vector<Clave>* vector) {
  for(int i = 0; i < vector->size(); ++i){
    vector->at(i) = MIN_INT + rand() % (MAX_INT - MIN_INT);
  }
}

int main (int argc, char* argv[]){

  int size;
  char opcion;
  std::cout << "Introduzca el tamaño del vector : ";
  std::cin >> size; 

  std::vector<int>* v = new std::vector<int>(size);

  std::cout << "vector aleatorio? s) si | n) no : ";
  std::cin >> opcion; 
  switch(opcion){
    case 's':
      fillRandVector(v);
      break;
    case 'n':
      for(int i = 0; i < v->size(); ++i)
        std::cin >> v->at(i);
      break;
  }

  bool quit = false;

  while (!quit) {
    show_menu();

    std::cin >> opcion; 

    fillRandVector(v); // Volvemos a poner el vector desordenado.
    std::cout << "vector desordenado:" << std::endl;
    mostrar_v(v);  

    switch(opcion){

      case 'q': quicksort<int>(v, 0, v->size()-1);
        break;

      case 'd':
        float alpha;
        do{
          std::cout << "Introduzca el incremento [0 < a < 1]: ";
          std::cin >> alpha;
        }while(!((alpha > 0) && (alpha < 1)));

        incr_dec<int>(v, alpha, v->size());

        break;

      case 'h': heapsort<int>(v, v->size());
        break;

      case 's': seleccion<int>(v, v->size());
        break;
      
      case 'k': quit = true;
        break;

      default: std::cout << "opcion no soportada" << std::endl;    
    }

    std::cout << "vector ordenado:" << std::endl;
    mostrar_v(v);
    std::cout << std::endl;
  }

  delete v;

  return 0;
}