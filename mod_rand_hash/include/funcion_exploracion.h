#ifndef _FUNCION_EXPLORACION_T_
#define _FUNCION_EXPLORACION_T_

#include <random>
#include "funcion_dispersion.h"

template<class Key>
class FuncionExploracion { 
  public:  
    virtual unsigned operator()(const Key& k, unsigned i)const = 0;
};

template<class Key>
class feLineal: public FuncionExploracion<Key>{
  public:
    unsigned operator()(const Key& k, unsigned i)const {
      return i;
    }
};

template<class Key>
class feCuadratica: public FuncionExploracion<Key>{ 
  public:
    unsigned operator()(const Key& k, unsigned i)const {
      return i*i;
    }
};

template<class Key>
class feDobleDispersion: public FuncionExploracion<Key>{
  public:
    feDobleDispersion(FuncionDispersion<Key>* fd): fd_(fd){}
    feDobleDispersion(void){delete fd_;}
    unsigned operator()(const Key& k, unsigned i)const {
      return fd_->operator()(k)*i;
    }

  private:
    FuncionDispersion<Key>* fd_;
};

template<class Key>
class feRedispersion: public FuncionExploracion<Key>{
  public:
  feRedispersion(FuncionDispersion<Key>* fdr):fdr_(fdr){}

    ~feRedispersion(void){
      delete fdr_;
    }
    unsigned operator()(const Key& k, unsigned i)const {
      return fdr_->operator()(i);
    }

  private:
    FuncionDispersion<Key>* fdr_;
};

#endif