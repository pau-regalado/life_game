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
    ABE(NodoAVL<Key>* raiz): AB<Key>(raiz){}
    // ~ABE(){}

    bool insertar(const Key dato);
    void insertarEquilibradoRama(const Key dato, NodoAVL<Key>* nodo);

    bool equilibrado(void);
    bool equilibrioRama(NodoAVL<Key>* nodo);

    // Busquedas
    bool buscar(const Key& X);
    bool buscarRama(NodoAVL<Key>* nodo, const Key& X);

    // Eliminacion no implementada en esta clase
    bool eliminar(const Key& X) { return false;}
};

template <class Key>
bool ABE<Key>::equilibrado(void){
  return equilibrioRama(this->getRaiz());
}

template <class Key>
bool ABE<Key>::equilibrioRama(NodoAVL<Key>* nodo){
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
      this->setRaiz(new NodoAVL<Key> (dato));
    } else {
      insertarEquilibradoRama(dato, this->getRaiz());
    }
    return true;
  } else {
    return false;
  }
}

template <class Key>
void ABE<Key>::insertarEquilibradoRama(const Key dato, NodoAVL<Key>* nodo){
  if (AB<Key>::tamRama(nodo->getIzq()) <= AB<Key>::tamRama(nodo->getDer())){
    if(nodo->getIzq() != nullptr){
      insertarEquilibradoRama(dato, nodo->getIzq());
    }else{
      NodoAVL<Key>* nuevo = new NodoAVL<Key>(dato);
      nodo->setIzq(nuevo);
    }
  }else{
    if(nodo->getDer() != nullptr){
      insertarEquilibradoRama(dato,nodo->getDer());
    }else{
      NodoAVL<Key>* nuevo = new NodoAVL<Key>(dato);
      nodo->setDer(nuevo);
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
bool ABE<Key>::buscarRama(NodoAVL<Key>* nodod, const Key& X) {
  std::queue<std::pair<NodoAVL<Key>*,int>> Q;
  NodoAVL<Key> *nodo;
  int nivel, Nivel_actual = 0;
  bool encontrado = false;
  Q.push(std::make_pair(this->getRaiz(), 0));

  //Recorremos la cola hasta que este vacia
  while (!Q.empty(  )) {
    //Guardamos el primer valor de la cola
    std::pair<NodoAVL<Key>*,int> p;
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

#endif