#include "../include/nodo.h"

template <class T>
nodo<T>::nodo(void){
  h_izq_ = nullptr;
  h_der_ = nullptr;
}

template <class T>
nodo<T>::nodo(T data, nodo<T>* izq, nodo<T>* der){
  data_ = data;
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