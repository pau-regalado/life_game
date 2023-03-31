#ifndef _BLOCK_
#define _BLOCK_

#include <vector>
#include <array>
#include <list>
#include <iostream>

#include "sequence.h"
 
template <class Key>
class Block: public Sequence<Key>{

  public:
    Block(const int Size = 0);
    Block(std::list<Key>& New);
    ~Block(void);

    virtual bool Buscarc(const Key& X);
    virtual bool Insertarc(const Key&X);
    virtual bool EstaLleno(void) const;

    virtual void Resize(int Size);
    void setMaxSize(int max);
    void print();
    
  private:
    int ocupado_;
    int MaxSize_;
};

// ----------------------------- IMPLEMENTATION -----------------------------

template <class Key>
Block<Key>::Block(int Size){
  ocupado_ = 0;
  MaxSize_ = Size;
  Sequence<Key>::Self_.resize(MaxSize_);
}

template <class Key>
Block<Key>::~Block(void){}

template <class Key>
bool Block<Key>::Buscarc(const Key& X) {
  bool encontrado = false;
  for (int i = 0; i < MaxSize_; ++i){
    if (Sequence<Key>::Self_.at(i) == X){
      encontrado = true;
    }
  }
  
  return encontrado;
}

template <class Key>
bool Block<Key>::Insertarc(const Key& X){
  bool no_esta = false;

  if (!EstaLleno() && !Buscarc(X)){
    Sequence<Key>::addInsertElements();
    Sequence<Key>::Self_.at(ocupado_) = X;
    ocupado_++;
    no_esta = true;
  }

  return no_esta;
}

template <class Key>
bool Block<Key>::EstaLleno(void) const{
  return !(ocupado_ < MaxSize_);
}

template <class Key>
void Block<Key>::Resize(int Size){
  Sequence<Key>::Self_.resize(Size);
  MaxSize_ = Size;
  ocupado_ = 0;
  for (int i = 0; i < MaxSize_; ++i){
    Sequence<Key>::Self_[i] = -1;
  }
}

template <class Key>
void Block<Key>::setMaxSize(int max){
  MaxSize_ = max;
}

template <class Key>
void Block<Key>::print() {
  for (int i = 0; i < Sequence<Key>::Self_.size(); ++i){
    std::cout << Sequence<Key>::Self_[i] << " ";
  } 
}

#endif