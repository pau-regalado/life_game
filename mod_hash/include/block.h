#ifndef _BLOCK_
#define _BLOCK_

#include <vector>
#include <array>
#include <list>
#include <iostream>

#include "sequence.h"
 
template <class Clave>
class Block: public Sequence<Clave>{

  public:

    Block(const int Size = 0);
    Block(std::list<Clave>& New);
    ~Block(void);

    virtual bool Buscarc(const Clave& X) const;
    virtual bool Insertarc(const Clave&X);
    virtual bool EstaLleno(void) const;

    virtual void Resize(int Size);
    void setMaxSize(int max);
    void print();
    
  private:
    int ocupado_;
    int MaxSize_;

};

// ----------------------------- IMPLEMENTATION -----------------------------

template <class Clave>
Block<Clave>::Block(int Size){
  ocupado_ = 0;
  MaxSize_ = Size;
  Sequence<Clave>::Self_.resize(MaxSize_);
}

template <class Clave>
Block<Clave>::~Block(void){

}

template <class Clave>
bool Block<Clave>::Buscarc(const Clave& X) const{

  bool encontrado = false;
  for (int i = 0; i < MaxSize_; ++i){
    if (Sequence<Clave>::Self_.at(i) == X){
      encontrado = true;
    }
  }

  return encontrado;
}

template <class Clave>
bool Block<Clave>::Insertarc(const Clave& X){
  
  bool no_esta = false;

  if (!EstaLleno()){
    if (!Buscarc(X)){
      Sequence<Clave>::Self_.at(ocupado_) = X;
      ocupado_++;
      no_esta = true;
    }
  }

  return no_esta;
}

template <class Clave>
bool Block<Clave>::EstaLleno(void) const{
  return !(ocupado_ < MaxSize_);
}

template <class Clave>
void Block<Clave>::Resize(int Size){
  Sequence<Clave>::Self_.resize(Size);
  MaxSize_ = Size;
  ocupado_ = 0;
  for (int i = 0; i < MaxSize_; ++i){
    Sequence<Clave>::Self_[i] = -1;
  }
}

template <class Clave>
void Block<Clave>::setMaxSize(int max){
  MaxSize_ = max;
}

template <class Clave>
void Block<Clave>::print() {
  for (int i = 0; i < Sequence<Clave>::Self_.size(); ++i){
    std::cout << Sequence<Clave>::Self_[i] << " ";
  } 
}

#endif