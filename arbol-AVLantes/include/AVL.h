#ifndef __AVL__
#define __AVL__

#include <iostream>
#include <queue>
#include <utility>

#include "ABB.h"

template <class Key>
class AVL: public ABB<Key>{

  public:
    AVL(void): ABB<Key>(nullptr){}
    AVL(NodoAVL<Key>* raiz): AB<Key>(raiz){}
    // ~AVL(){}

    bool insertar(const Key dato);
    bool insertarRama(const Key dato, NodoAVL<Key>* &nodo);

    bool equilibrado(void);
    bool equilibrioRama(NodoAVL<Key>* nodo);

    // Busquedas
    bool buscar(const Key& X);
    bool buscarRama(NodoAVL<Key>* nodo, const Key& X);

    void rotacionII(NodoAVL<Key>* &eliminado);
    void rotacionID(NodoAVL<Key>* &eliminado);
    void rotacionDI(NodoAVL<Key>* &eliminado);
    void rotacionDD(NodoAVL<Key>* &eliminado);

    // Eliminacion no implementada en esta clase
    void sustituye(NodoAVL<Key>* &eliminado, NodoAVL<Key>* &sustituto);
    bool eliminar(const Key& X);
    bool eliminarRama(NodoAVL<Key>* &nodo, const Key& X);

  private:
    Key clave_;
};

template <class Key>
bool AVL<Key>::equilibrado(void){
  return equilibrioRama(this->getRaiz());
}

template <class Key>
void AVL<Key>::rotacionII(NodoAVL<Key>* &eliminado) {

}

template <class Key>
bool AVL<Key>::equilibrioRama(NodoAVL<Key>* nodo){
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
bool AVL<Key>::insertar(const Key dato) {
  if (buscar(dato))
   return false;
  else
    return insertarRama(dato, this->getRaiz());
}

template <class Key>
bool AVL<Key>::insertarRama(const Key dato, NodoAVL<Key>* &nodo){
  if (nodo == nullptr) {
    nodo = new NodoAVL<Key>(dato,dato);
    return true;
  } else if (dato < nodo->getData()) {
    return insertarRama(dato, nodo->getIzq());
  } else {
    return insertarRama(dato, nodo->getDer());
  }
}

template <class Key>
bool AVL<Key>::buscar(const Key& X) {
  return buscarRama(this->getRaiz(), X);
}

template <class Key>
bool AVL<Key>::buscarRama(NodoAVL<Key>* nodo, const Key& X) {
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
void AVL<Key>::sustituye(NodoAVL<Key>* &eliminado, NodoAVL<Key>* &sustituto) {
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
bool  AVL<Key>::eliminar(const Key& X) {
  return eliminarRama(this->getRaiz(), X);
}

template <class Key>
bool  AVL<Key>::eliminarRama(NodoAVL<Key>* &nodo, const Key& clave) {
  if (!nodo) {
    return false;
  }
  if (clave < nodo->getData()) {
    return eliminarRama(nodo->getIzq(), clave);
  } else if (clave > nodo->getData()) {
    return eliminarRama(nodo->getDer(), clave);
  } else {
    NodoAVL<Key>* eliminado = nodo;
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