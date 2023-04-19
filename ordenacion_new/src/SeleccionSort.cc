#include "../include/SeleccionSort.h"
#include "../include/seleccion.h"

template<class Key>

void SeleccionSort<Key>::seleccionarSort() {
  seleccionar<Key>(seq_, size_);
}

template<class Key>
void SeleccionSort<Key>::Sort() {
  seleccion<Key>(seq_, size_);
}