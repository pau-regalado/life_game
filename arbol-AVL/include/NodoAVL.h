#ifndef __NODOBB__
#define __NODOBB__

#include <iostream>
#include "NodoB.h"

template <class Key>
class NodoAVL: public NodoB{
  public:
    NodoAVL(void);
    NodoAVL(Key data, Key clave = 0, NodoAVL<Key>* izq = nullptr, NodoAVL<Key>* der = nullptr)
          : NodoB{data, izq, der}{}
    // getter / setters 
    int    getBal(void);
    void setBal(int factor);

    NodoAVL<Key>& operator=(const NodoAVL<Key> &p);

  private:
    int bal_;
};

template <class Key>
int NodoAVL<Key>::getBal(void){
  return bal_;
}

template <class Key>
void NodoAVL<Key>::setBal(int factor){
  bal_ = factor;
}

template <class Key>
NodoAVL<Key>& NodoAVL<Key>::operator=(const NodoAVL<Key> &nodo) {
  if (this != &nodo) {
    this->data_  = nodo.getData();
    this->bal_  = nodo.getbal();
    this->h_der_ = nodo.getDer();
    this->h_izq_ = nodo.getIzq();
  }
  return *this;
}

#endif