#ifndef __NODOB__
#define __NODOB__

#include <iostream>

template <class T>
class NodoB{
  public:
    NodoB(void);
    NodoB(T data, NodoB<T>* izq = nullptr, NodoB<T>* der = nullptr);
    ~NodoB(void);
    // getter / setters 

    NodoB<T>* getIzq (void);
    NodoB<T>* getDer (void);
    T         getData(void);


    void setIzq (NodoB<T>* izq);
    void setDer (NodoB<T>* der);    
    void setData(T data);

    NodoB<T>& operator=(const NodoB<T> &p);

  private:
    T data_;
    T clave_;
    NodoB<T>* h_der_;
    NodoB<T>* h_izq_;
};

template <class T>
NodoB<T>::NodoB(void){
  h_izq_ = nullptr;
  h_der_ = nullptr;
}

template <class T>
NodoB<T>::NodoB(T data, NodoB<T>* izq, NodoB<T>* der){
  data_ = data;
  h_izq_ = izq;
  h_der_ = der;
}

// Destruye el nodo
template <class T>
NodoB<T>::~NodoB(void){
  if (h_izq_) {delete h_izq_;} // Antes !h_izq_
  if (h_der_) {delete h_der_;}
}

template <class T>
NodoB<T>* NodoB<T>::getIzq(void){
  return h_izq_;
}

template <class T>
NodoB<T>* NodoB<T>::getDer(void){
  return h_der_;
}

template <class T>
T NodoB<T>::getData(void){
  return data_;
}

template <class T>
void NodoB<T>::setIzq(NodoB<T>* izq){
  h_izq_ = izq;
}

template <class T>
void NodoB<T>::setDer(NodoB<T>* der){
  h_der_ = der;
}

template <class T>
void NodoB<T>::setData(T data){
  data_ = data;
}

template <class T>
NodoB<T>& NodoB<T>::operator=(const NodoB<T> &nodo) {
  if (this != &nodo) {
    this->data_  = nodo.getData();
    this->h_der_ = nodo.getDer();
    this->h_izq_ = nodo.getIzq();
  }
  return *this;
}

#endif