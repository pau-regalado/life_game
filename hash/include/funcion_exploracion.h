#ifndef _FUNCION_EXPLORACION_T_
#define _FUNCION_EXPLORACION_T_

#include <random>

#include "funcion_dispersion.h"

template<class Clave>
class FuncionExploracion { 
  public:
  
    virtual unsigned operator()(const Clave& k, unsigned i)const = 0;
    
};

template<class Clave>
class feLineal: public FuncionExploracion<Clave>{
  
  public:
    unsigned operator()(const Clave& k, unsigned i)const {
      return i;
    }
};

template<class Clave>
class feCuadratica: public FuncionExploracion<Clave>{
  
  public:
    unsigned operator()(const Clave& k, unsigned i)const {
      return i*i;
    }
};

template<class Clave>
class feDobleDispersion: public FuncionExploracion<Clave>{

  public:

    feDobleDispersion(FuncionDispersion<Clave>* fd): fd_(fd){}
    feDobleDispersion(void){delete fd_;}
    unsigned operator()(const Clave& k, unsigned i)const {
      return fd_->operator()(k)*i;
    }

  private:
    FuncionDispersion<Clave>* fd_;
};

template<class Clave>
class feRedispersion: public FuncionExploracion<Clave>{
  
  public:
  feRedispersion(FuncionDispersion<Clave>* fdr):fdr_(fdr){}

    ~feRedispersion(void){
      delete fdr_;
    }
    unsigned operator()(const Clave& k, unsigned i)const {
      return fdr_->operator()(i);
    }

  private:

    FuncionDispersion<Clave>* fdr_;

};



#endif












/* 

      fdModulo<int> fm(tamano);
      fdrandom<int> fr(tamano);
      fe = new feRedispersion<int>(&fm,&fr);
 */