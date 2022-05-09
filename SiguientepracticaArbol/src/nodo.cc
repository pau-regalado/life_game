#include "../include/nodo.h"

template <class T>
nodo<T>::nodo(void){
  h_izq_ = nullptr;
  h_der_ = nullptr;
}

template <class T>
nodo<T>::nodo(T data, T clave, nodo<T>* izq, nodo<T>* der){
  data_ = data;
  clave_ = clave;
  h_izq_ = izq;
  h_der_ = der;
}

template <class T>
nodo<T>::~nodo(void){
  if (!h_izq_) {delete h_izq_;}
  if (!h_der_) {delete h_der_;}
}

template <class T>
nodo<T>* nodo<T>::get_izq(void){
  return h_izq_;
}

template <class T>
nodo<T>* nodo<T>::get_der(void){
  return h_der_;
}

template <class T>
T nodo<T>::get_data(void){
  return data_;
}

template <class T>
T nodo<T>::get_clave(void){
  return clave_;
}

template <class T>
void nodo<T>::set_izq(nodo<T>* izq){
  h_izq_ = izq;
}

template <class T>
void nodo<T>::set_der(nodo<T>* der){
  h_der_ = der;
}

template <class T>
void nodo<T>::set_data(T data){
  data_ = data;
}

template <class T>
void nodo<T>::set_clave(T clave){
  clave_ = clave;
}

template <class T>
nodo<T>& nodo<T>::operator= (nodo<T>& node){
  clave_ = node->get_clave();
  data_ = node->get_data();
  h_der_ = node->get_der();
  h_izq_ = node->get_izq();
  return *this;
}