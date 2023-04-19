#include "../include/InsercionSort.h"
#include "../include/insercion.h"

template<class Key>

void InsercionSort<Key>::Sort() {
  insercion<Key>(seq, size);
}