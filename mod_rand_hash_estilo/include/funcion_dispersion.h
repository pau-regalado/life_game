#ifndef _FUNCION_DISPERSION_T_
#define _FUNCION_DISPERSION_T_
#include <random>

template<class Key>
class FuncionDispersion{
  
  public:
    virtual unsigned operator()(const Key& k) const = 0;
};

template<class Key>
class fdModulo: public FuncionDispersion<Key>{
  public:

    fdModulo(const unsigned n): nDatos(n){}
    
    unsigned operator()(const Key& k) const {
      return k % nDatos;
    }
  private:
    unsigned nDatos;
};

template<class Key>
class fdSuma: public FuncionDispersion<Key>{
  public:
    fdSuma(const unsigned n): nDatos(n){}
    
    unsigned operator()(const Key& k) const {
      int y, d = 0;
      int x = k;
      while (x > 0) {
        y = x % 10;
        d += y;
        x /= 10;
      }
      return d % nDatos;
    }
  private:
    unsigned nDatos;
};

template<class Key>
class fdrandom: public FuncionDispersion<Key>{
  public:

    fdrandom(const unsigned n): nDatos(n){}
    
    unsigned operator()(const Key& k) const {
      srand(k);
      return rand() % nDatos;
    }
  private:
    unsigned nDatos;
};

#endif
