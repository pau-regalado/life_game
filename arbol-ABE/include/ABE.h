#ifndef __ABE__
#define __ABE__

#include <iostream>
#include <queue>
#include <utility>

#include "AB.h"

template <class Key>
class ABE: public AB<Key>{

  public:
    ABE(void): AB<Key>(nullptr){}
    ABE(NodoB<Key>* raiz): AB<Key>(raiz){}
    // ~ABE(){}

    bool insertar(const Key dato);
    void insertarEquilibradoRama(const Key dato, NodoB<Key>* nodo);

    bool equilibrado(void);
    bool equilibrioRama(NodoB<Key>* nodo);

    // Busquedas
    bool buscar(const Key& X);
    bool buscarRama(NodoB<Key>* nodo, const Key& X);
};

template <class Key>
bool ABE<Key>::equilibrado(void){
  return equilibrioRama(this->getRaiz());
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
bool ABE<Key>::insertar(const Key dato) {
  if (!buscar(dato)) {
    if (this->getRaiz() == nullptr) {
      this->setRaiz(new NodoB<Key> (dato));
    } else {
      insertarEquilibradoRama(dato, this->getRaiz());
    }
    return true;
  } else {
    return false;
  }
}

template <class Key>
void ABE<Key>::insertarEquilibradoRama(const Key dato, NodoB<Key>* nodo){
  if (AB<Key>::tamRama(nodo->getIzq()) <= AB<Key>::tamRama(nodo->getDer())){
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

template <class Key>
bool ABE<Key>::buscar(const Key& X) {
  if (this->getRaiz()) {
    return buscarRama(this->getRaiz(), X);
  } else {
    return false;
  }
}

template <class Key>
bool ABE<Key>::buscarRama(NodoB<Key>* nodod, const Key& X) {
  std::queue<std::pair<NodoB<Key>*,int>> Q;
  NodoB<Key> *nodo;
  int nivel, Nivel_actual = 0;
  bool encontrado = false;
  Q.push(std::make_pair(this->getRaiz(), 0));

  //Recorremos la cola hasta que este vacia
  while (!Q.empty()) {
    //Guardamos el primer valor de la cola
    std::pair<NodoB<Key>*,int> p;
    p = Q.front();
    nodo = p.first;
    nivel = p.second;
    //Quitamos la pareja(nodo,nivel) de la Cola
    Q.pop();
    if(nivel > Nivel_actual) {
      Nivel_actual = nivel;
    }
    //Mostramos el valor del nodo
    if (nodo != NULL) {
      if (nodo->getData() == X) {
        encontrado = true;
      }
      Q.push(std::make_pair(nodo->getIzq(),nivel + 1));
      Q.push(std::make_pair(nodo->getDer(),nivel + 1));
    }
  }
  return encontrado;
}
/*
template <class Key>
bool ABE<Key>::buscarRama(NodoB<Key>* nodo, const Key& X) {
  if (!nodo) {return false;}
  if (nodo->getData() == X) {return true;}
  return (buscarRama(nodo->getIzq(), X) || buscarRama(nodo->getDer(), X));
}*/

#endif