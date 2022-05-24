#ifndef __NODOB__
#define __NODOB__

#include <iostream>

template <class Key>
class NodoAVL{
  public:
    NodoAVL(void);
    NodoAVL(Key data = 0, Key clave = 0, NodoAVL<Key>* izq = nullptr, NodoAVL<Key>* der = nullptr);
    ~NodoAVL(void);
    // getter / setters 

    NodoAVL<Key>* &getIzq (void);
    NodoAVL<Key>* &getDer (void);
    Key         getData(void);
    Key         getClave(void);

    void setIzq (NodoAVL<Key>* &izq);
    void setDer (NodoAVL<Key>* &der);   
    void setClave(Key clave);
    void setData(Key data);
    int& getBal(void);
    void setBal(int factor);

    NodoAVL<Key>& operator=(const NodoAVL<Key> &p);
  protected:
    Key data_;
    Key clave_;
    int bal_;
    NodoAVL<Key>* h_der_;
    NodoAVL<Key>* h_izq_;
};

template <class Key>
NodoAVL<Key>::NodoAVL(void){
  h_izq_ = nullptr;
  h_der_ = nullptr;
}

template <class Key>
NodoAVL<Key>::NodoAVL(Key data, Key clave, NodoAVL<Key>* izq, NodoAVL<Key>* der){
  data_ = data;
  clave_ = clave;
  h_izq_ = izq;
  h_der_ = der;
}

// Destruye el nodo
template <class Key>
NodoAVL<Key>::~NodoAVL(void){
  if (!h_izq_) {delete h_izq_;}
  if (!h_der_) {delete h_der_;}
}

template <class Key>
NodoAVL<Key>* &NodoAVL<Key>::getIzq(void){
  return h_izq_;
}

template <class Key>
NodoAVL<Key>* &NodoAVL<Key>::getDer(void){
  return h_der_;
}

template <class Key>
Key NodoAVL<Key>::getData(void){
  return data_;
}
template <class Key>
Key NodoAVL<Key>::getClave(void){
  return clave_;
}

template <class Key>
void NodoAVL<Key>::setClave(Key clave){
  clave_ = clave;
}

template <class Key>
void NodoAVL<Key>::setIzq(NodoAVL<Key>* &izq){
  h_izq_ = izq;
}

template <class Key>
void NodoAVL<Key>::setDer(NodoAVL<Key>* &der){
  h_der_ = der;
}

template <class Key>
void NodoAVL<Key>::setData(Key data){
  data_ = data;
}

template <class Key>
int& NodoAVL<Key>::getBal(void){
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
    this->bal_   = nodo.getbal();
    this->h_der_ = nodo.getDer();
    this->h_izq_ = nodo.getIzq();
  }
  return *this;
}

#endif