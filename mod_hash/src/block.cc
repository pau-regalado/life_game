#include "../include/block.h"

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

/*
template <class Clave>
std::vector<Clave> Block<Clave>::get_self(void){
  return Self_;
}*/