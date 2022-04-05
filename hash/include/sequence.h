#ifndef _SEQUENCE_
#define _SEQUENCE_

#include <vector>
#include <array>
#include <list>
#include <iostream>
 
template <class Clave>
class Sequence{

  public:

    Sequence(const int Size = 0){}
    ~Sequence(void){}

    virtual bool Buscarc  (const Clave& X) const = 0;
    virtual bool Insertarc(const Clave&X) = 0;
    virtual bool EstaLleno(void) const = 0;
    virtual void Resize(int size) = 0;
    virtual void print() = 0;

    Clave at(int i){
      return Self_[i];
    }

    std::vector<Clave>& get_self(void);

  protected:

    std::vector<Clave> Self_;

};


template <class Clave>
std::vector<Clave>& Sequence<Clave>::get_self(void){
  return Self_;
}

#endif