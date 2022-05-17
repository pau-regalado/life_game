#ifndef __ABB__
#define __ABB__

#include <iostream>
#include <queue>
#include <utility>

#include "AB.h"

template <class Key>
class ABB: public AB<Key>{

  public:
    ABB(void): AB<Key>(nullptr){}
    ABB(NodoB<Key>* raiz): AB<Key>(raiz){}
    // ~ABB(){}

    bool insertar(const Key dato);
    bool insertarRama(const Key dato, NodoB<Key>* &nodo);

    bool equilibrado(void);
    bool equilibrioRama(NodoB<Key>* nodo);

    // Busquedas
    bool buscar(const Key& X);
    bool buscarRama(NodoB<Key>* nodo, const Key& X);

    // Eliminacion no implementada en esta clase
    void sustituye(NodoB<Key>* &eliminado, NodoB<Key>* &sustituto);
    bool eliminar(const Key& X);
    bool eliminarRama(NodoB<Key>* &nodo, const Key& X);

  private:
    Key clave_;
};

template <class Key>
bool ABB<Key>::equilibrado(void){
  return equilibrioRama(this->getRaiz());
}

template <class Key>
bool ABB<Key>::equilibrioRama(NodoB<Key>* nodo){
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
bool ABB<Key>::insertar(const Key dato) {
  if (buscar(dato))
   return false;
  else
    return insertarRama(dato, this->getRaiz());
}

template <class Key>
bool ABB<Key>::insertarRama(const Key dato, NodoB<Key>* &nodo){
  if (nodo == nullptr) {
    nodo = new NodoB<Key>(dato,dato);
    return true;
  } else if (dato < nodo->getData()) {
    return insertarRama(dato, nodo->getIzq());
  } else {
    return insertarRama(dato, nodo->getDer());
  }
}

template <class Key>
bool ABB<Key>::buscar(const Key& X) {
  return buscarRama(this->getRaiz(), X);
}

template <class Key>
bool ABB<Key>::buscarRama(NodoB<Key>* nodo, const Key& X) {
  if (!nodo) {
    return false;
  }
  if (X == nodo->getData()) {
    return true;
  }
  if (X < nodo->getData())
    return buscarRama(nodo->getIzq(), X);
  return buscarRama(nodo->getDer(), X);
}

template <class Key>
void ABB<Key>::sustituye(NodoB<Key>* &eliminado, NodoB<Key>* &sustituto) {
  if (sustituto->getDer()) {
    sustituye(eliminado, sustituto->getDer());
  } else {
    eliminado->setClave(sustituto->getClave());
    eliminado->setData(sustituto->getData());
    eliminado = sustituto;
    sustituto = sustituto->getIzq();
  }
}

template <class Key>
bool  ABB<Key>::eliminar(const Key& X) {
  return eliminarRama(this->getRaiz(), X);
}

template <class Key>
bool  ABB<Key>::eliminarRama(NodoB<Key>* &nodo, const Key& clave) {
  if (!nodo) {
    return false;
  }
  if (clave < nodo->getData()) {
    return eliminarRama(nodo->getIzq(), clave);
  } else if (clave > nodo->getData()) {
    return eliminarRama(nodo->getDer(), clave);
  } else {
    NodoB<Key>* eliminado = nodo;
    if (!nodo->getDer()) {
      nodo = nodo->getIzq();
    } else if (!nodo->getIzq()) {
      nodo = nodo->getDer();
    } else {
      sustituye(eliminado, nodo->getIzq());
    }
    delete eliminado;
    return true;
  }
}

#endif