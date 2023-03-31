#ifndef _LIST_
#define _LIST_

#include <vector>
#include <array>
#include <list>
#include <iostream>

#include "sequence.h"
 
template <class Key>
class List: public Sequence<Key>{

  public:
    List(const int Size = 0);
    ~List(void);

    bool Buscarc(const Key& X);
    bool Insertarc(const Key&X);
    bool EstaLleno(void) const;

    void Resize(int Size){}
    // void print();
};

// ----------------------------- IMPLEMENTATION -----------------------------

template <class Key>
List<Key>::List(int Size){}

template <class Key>
List<Key>::~List(void){}

template <class Key>
bool List<Key>::Buscarc(const Key& X) {
  Sequence<Key>::addSearchTry();
  bool encontrado = false;
  for (int i = 0; i < Sequence<Key>::Self_.size(); ++i){
    if (Sequence<Key>::Self_[i] == X){
      encontrado = true;
    }
  }
  return encontrado;
}

template <class Key>
bool List<Key>::Insertarc(const Key& X){
  Sequence<Key>::addInsertTry();
  bool insert = false;
  if (!Buscarc(X)){
    Sequence<Key>::Self_.push_back(X);
    insert = true;
  }
  return insert;
}

template <class Key>
bool List<Key>::EstaLleno(void) const{
  return false; // Por definicion, nunca esta lleno
}

#endif