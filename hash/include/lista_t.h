#ifndef _LISTA_T_
#define _LISTA_T_

#include <vector>
#include <array>
#include <list>
#include <iostream>
 
template <class Clave>
class Lista_t{

  public:

    Lista_t(const int Size = 0);
    Lista_t(std::list<Clave>& New);
    ~Lista_t(void);

    bool Buscarc(const Clave& X) const;
    bool Insertarc(const Clave&X);
    bool EstaLleno(void) const;
    void Resize(int size);

    std::vector<Clave> get_self(void);

  private:

    unsigned Ocupado_;
    unsigned MaxSize_;
    std::vector<Clave> Self_;

};

#endif