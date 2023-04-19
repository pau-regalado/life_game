#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <chrono>

#include "../include/quickSort.h"
#include "../include/mergeSort.h"
#include "../include/incrDec.h"
#include "../include/heapSort.h"
#include "../include/seleccion.h"
#include "../include/insercion.h"
#include "../include/radixSort.h"
using namespace std;
using namespace std::chrono;

const int MAX_INT = 9999;
const int MIN_INT = 1000;

void show_menu(void){
  std::cout << "Método de ordenación: " << std::endl;
  std::cout << "d) Incrementos decrecientes" << std::endl;
  std::cout << "h) Heapsort" << std::endl;
  std::cout << "s) Seleccion" << std::endl;
  std::cout << "i) Insercion" << std::endl;
  std::cout << "r) RadixSort" << std::endl;
  std::cout << "m) MergeSort" << std::endl;
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

  std::vector<long>* v = new std::vector<long>(size);

 
  std::cout << "vector aleatorio? s) si | n) no : ";
  std::cin >> opcion; 
  switch(opcion){
    case 's':
      fillRandVector(v);
      break;
    case 'n':
    int n;
      for(int i = 0; i < v->size(); ++i){
        std::cout << "Introduzca un numero: " << std::endl;
        std::cin >> n;
        v->at(i) = n;
      }
      break;
  }


  bool quit = false;

  SortMethod<long>* sorter;

  while (!quit) {
    show_menu();

    std::cin >> opcion; 

    fillRandVector(v); // Volvemos a poner el vector desordenado.
    std::cout << "vector desordenado:" << std::endl;
    mostrar_v(v);  

    switch(opcion){
      /*
      case 'q': quicksort<int>(v, 0, v->size()-1);
        break;
      */
      case 'd':
        float alpha;
        int index, ini, cent, fin;
        do{
          std::cout << "Introduzca el incremento [0 < a < 1]: ";
          std::cin >> alpha;
        }while(!((alpha > 0) && (alpha < 1)));

        sorter = new IncrDecMethod<long>(v, alpha ,v->size());
        break;
      case 'i':
        sorter = new InsercionMethod<long>(v, v->size());
        break;
      case 'h': 
        sorter = new HeapSortMethod<long>(v, v->size());
        break;
      case 's':
        sorter = new SeleccionMethod<long>(v, v->size());
        break;
      case 'r': 
        sorter = new RadixSortMethod<long>(v, v->size());
        break;
      case 'm': 
        sorter = new MergeSortMethod<long>(v, v->size());
        break;
      case 'o': 
        //auto start = high_resolution_clock::now();
        //auto stop = high_resolution_clock::now();
        chrono.start();
        std::cout << "Insersion: " << chrono.duration() << std::endl;
        chrono.stop();

        chrono.start();
        std::cout << "Seleccion: " << chrono.duration() << std::endl;
        chrono.stop();

        chrono.start();
        std::cout << "Insersion: " << chrono.duration() << std::endl;
        chrono.stop();
        break;
      case 'k': quit = true;
        break;

      default: std::cout << "opcion no soportada" << std::endl;    
    }

    // Ordenamos el vector
    sorter->Sort();
    std::cout << "vector ordenado:" << std::endl;
    mostrar_v(v);
    std::cout << std::endl;
  }

  delete v;
  delete sorter;

  return 0;
}