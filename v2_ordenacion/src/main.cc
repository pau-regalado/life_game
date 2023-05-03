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
  fillRandVector(v); // Volvemos a poner el vector desordenado.
  std::vector<long> copy = *v;

  SortMethod<long>* sorter;

  float alpha = 0.8;
  sorter = new IncrDecMethod<long>(v, alpha ,v->size());
  std::cout << "IncrDecMethod: " << sorter->sort_time().count() << " ms." << std::endl;
  *v = copy;

  sorter = new InsercionMethod<long>(v, v->size());
  std::cout << "InsercionMethod: " << sorter->sort_time().count() << " ms." << std::endl;
  *v = copy;

  sorter = new HeapSortMethod<long>(v, v->size());
  std::cout << "HeapSortMethod: " << sorter->sort_time().count() << " ms." << std::endl;
  *v = copy;

  sorter = new SeleccionMethod<long>(v, v->size());
  std::cout << "SeleccionMethod: " << sorter->sort_time().count() << " ms." << std::endl;
  *v = copy;

  sorter = new RadixSortMethod<long>(v, v->size());
  std::cout << "RadixSortMethod: " << sorter->sort_time().count() << " ms." << std::endl;
  *v = copy;

  sorter = new MergeSortMethod<long>(v, v->size());
  std::cout << "MergeSortMethod: " << sorter->sort_time().count() << " ms." << std::endl;
  *v = copy;

  delete v;
  delete sorter;

  return 0;
}