#ifndef _TABLA_HASH_T_
#define _TABLA_HASH_T_

#include <vector>
#include <array>
#include <iostream>

#include "lista_t.h"
#include "funcion_dispersion.h"
#include "funcion_exploracion.h"

const unsigned kDefaultSize = 10;
const unsigned kDefaultVector = 3;

template <class Clave>
class Tabla_hash_t{

  public:

    Tabla_hash_t(FuncionDispersion<Clave>* fd,
                 FuncionExploracion<Clave>* fe,
                 unsigned nDatos = kDefaultSize,
                 unsigned nSinonimos = kDefaultVector);

    ~Tabla_hash_t(void);
    bool Buscar(Clave& X);
    bool Insertar(Clave& X);
    void showTabla(void);
    void sumar_intento(void);
    std::vector<Lista_t<Clave>> get_v(void);
    void change_fe(FuncionExploracion<Clave>* newfe);
    int get_intentos(void);

  private:

    unsigned nDatos_;
    unsigned nSinonimos_;
    std::vector<Lista_t<Clave>> vDatos_;
    FuncionDispersion<Clave>* fd_;
    FuncionExploracion<Clave>* fe_;
    int intentos_;

};

#endif