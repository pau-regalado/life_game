#include "../include/ABE.h"

template <class Key>
bool ABE<Key>::equilibrado(void){
  return equilibrioRama(*this.getRaiz());
}

template <class Key>
bool ABE<Key>::equilibrioRama(NodoB<Key>* nodo){
  if(nodo == nullptr){return true;}

  int eq = tamRama(nodo->getIzq()) - tamRama(nodo->getDer());

  switch (eq){
    case -1:
      break;
    case 0:
      break;
    case 1: 
      return equilibrioRama(nodo->getIzq()) && equilibrioRama(nodo->getDer());
    default: return false;
  }
}

template <class Key>
void ABE<Key>::insertar(const Key dato) {
  if (*this.getRaiz() == nullptr) {
    *this.setRaiz(new NodoB<Key> (dato));
  } else {
    insertarEquilibradoRama(dato, *this.getRaiz());
  }
}

template <class Key>
void ABE<Key>::insertarEquilibradoRama(const Key dato, NodoB<Key>* nodo){
  if (tamRama(nodo->getIzq()) <= tamRama(nodo->getDer())){
    if(nodo->getIzq() != nullptr){
      insertarEquilibradoRama(dato, nodo->getIzq());
    }else{
      nodo->setIzq(new NodoB<Key>(dato));
    }
  }else{
    if(nodo->getDer() != nullptr){
      insertarEquilibradoRama(dato,nodo->getDer());
    }else{
      nodo->setDer(new NodoB<Key>(dato));
    }
  }
}