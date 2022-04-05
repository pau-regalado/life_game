#ifndef _LIST_
#define _LIST_

#include <vector>
#include <array>
#include <list>
#include <iostream>

#include "sequence.h"
 
template <class Clave>
class List: public Sequence<Clave>{

  public:

    List(const int Size = 0);
    ~List(void);

    bool Buscarc(const Clave& X) const;
    bool Insertarc(const Clave&X);
    bool EstaLleno(void) const;

    void Resize(int Size){}
    void print();

};

// ----------------------------- IMPLEMENTATION -----------------------------

template <class Clave>
List<Clave>::List(int Size){
}

template <class Clave>
List<Clave>::~List(void){

}

template <class Clave>
bool List<Clave>::Buscarc(const Clave& X) const{

  bool encontrado = false;
  for (int i = 0; i < Sequence<Clave>::Self_.size(); ++i){
    if (Sequence<Clave>::Self_[i] == X){
      encontrado = true;
    }
  }
  return encontrado;
}

template <class Clave>
bool List<Clave>::Insertarc(const Clave& X){
  
  bool insert = false;
  if (!Buscarc(X)){
    Sequence<Clave>::Self_.push_back(X);
    insert = true;
  }
  return insert;
}

template <class Clave>
bool List<Clave>::EstaLleno(void) const{
  return false; // Por definicion, nunca esta lleno
}

template <class Clave>
void List<Clave>::print() {
  for (int i = 0; i < Sequence<Clave>::Self_.size(); ++i){
    std::cout << Sequence<Clave>::Self_[i] << " ";
  } 
}

#endif