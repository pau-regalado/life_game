#ifndef __NODOBB__
#define __NODOBB__

#include <iostream>
#include "NodoB.h"

template <class T>
class NodoBB: public NodoB{
  public:
    NodoBB(void);
    NodoBB(int clave, T data, NodoBB<T>* izq = nullptr, NodoBB<T>* der = nullptr)
          : clave_{clave}, NodoB{data, izq, der}{}
    // getter / setters 
    int    getClave(void);
    void setClave(int data);

    NodoBB<T>& operator=(const NodoBB<T> &p);

  private:
    int clave_;
};

template <class T>
int NodoBB<T>::getClave(void){
  return clave_;
}

template <class T>
void NodoBB<T>::setClave(int clave){
  clave_ = clave;
}

template <class T>
NodoBB<T>& NodoBB<T>::operator=(const NodoBB<T> &nodo) {
  if (this != &nodo) {
    this->data_  = nodo.getData();
    this->clave_  = nodo.getClave();
    this->h_der_ = nodo.getDer();
    this->h_izq_ = nodo.getIzq();
  }
  return *this;
}

#endif