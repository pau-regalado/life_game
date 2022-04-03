#include "../include/lista_t.h"

template <class Clave>
Lista_t<Clave>::Lista_t(int Size){
  Ocupado_ = 0;
  MaxSize_ = Size;
  Self_.resize(MaxSize_);
}

template <class Clave>
Lista_t<Clave>::~Lista_t(void){

}

template <class Clave>
bool Lista_t<Clave>::Buscarc(const Clave& X) const{

  bool encontrado = false;
  for (int i = 0; i < MaxSize_; ++i){
    //std::cout << Self_.at(i) << std::endl;
    if (Self_.at(i) == X){
      encontrado = true;
    }
  }

  return encontrado;
}

template <class Clave>
bool Lista_t<Clave>::Insertarc(const Clave& X){
  
  bool no_esta = false;

  if (!EstaLleno()){
    if (!Buscarc(X)){
      Self_.at(Ocupado_) = X;
      Ocupado_++;
      no_esta = true;
    }
  }

  return no_esta;
}

template <class Clave>
bool Lista_t<Clave>::EstaLleno(void) const{
  return !(Ocupado_ < MaxSize_);
}

template <class Clave>
void Lista_t<Clave>::Resize(int Size){
  Self_.resize(Size);
  MaxSize_ = Size;
  for (int i = 0; i < MaxSize_; ++i){
    Self_.at(i) = -1;
  }
}

template <class Clave>
std::vector<Clave> Lista_t<Clave>::get_self(void){
  return Self_;
}