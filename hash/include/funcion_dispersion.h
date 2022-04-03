#ifndef _FUNCION_DISPERSION_T_
#define _FUNCION_DISPERSION_T_

#include <random>

template<class Clave>
class FuncionDispersion{
  
  public:
    virtual unsigned operator()(const Clave& k) const = 0;
};

template<class Clave>
class fdModulo: public FuncionDispersion<Clave>{
  public:

    fdModulo(const unsigned n): nDatos(n){}
    
    unsigned operator()(const Clave& k) const {
      return k % nDatos;
    }
  private:
    unsigned nDatos;
  };

template<class Clave>
class fdrandom: public FuncionDispersion<Clave>{
  public:

    fdrandom(const unsigned n): nDatos(n){}
    
    unsigned operator()(const Clave& k) const {
      srand(k);
      return rand() % nDatos;
    }
  private:
    unsigned nDatos;
  };

#endif
