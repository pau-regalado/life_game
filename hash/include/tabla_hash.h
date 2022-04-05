#ifndef _TABLA_HASH_T_
#define _TABLA_HASH_T_

#include <vector>
#include <array>
#include <iostream>

#include "sequence.h"
#include "list.h"
#include "block.h"
#include "funcion_dispersion.h"
#include "funcion_exploracion.h"

const unsigned kDefaultSize = 10;
const unsigned kDefaultVector = 3;

//template <class Clave>
//class Sequence;

template <class Clave>
class Tabla_hash_t{

  public:

    Tabla_hash_t(unsigned tableSize = 0,
                 unsigned blockSize = 0,
                 FuncionDispersion<Clave>* fd = nullptr,
                 FuncionExploracion<Clave>* fe = nullptr);

    ~Tabla_hash_t(void);
    bool Buscar(Clave& X);
    bool Insertar(Clave& X);
    void showTabla(void);
    void sumar_intento(void);
    std::vector<Sequence<Clave>*>& get_v(void);
    void change_fe(FuncionExploracion<Clave>* newfe);
    int get_intentos(void);

  private:

    unsigned tableSize_;
    unsigned blockSize_;
    std::vector<Sequence<Clave>*> table_;
    FuncionDispersion<Clave>* fd_;
    FuncionExploracion<Clave>* fe_;
    int intentos_;

};

// ----------------------------- IMPLEMENTATION -----------------------------

template <class Clave>
Tabla_hash_t<Clave>::Tabla_hash_t(unsigned tableSize,
                                  unsigned blockSize,
                                  FuncionDispersion<Clave>* fd,
                                  FuncionExploracion<Clave>* fe){
  tableSize_ = tableSize;
  fd_ = fd;
  blockSize_ = blockSize;
  intentos_ = 0;
  
  table_.resize(tableSize);
  for (int i = 0; i < tableSize_; ++i){
    table_[i] = new List<Clave>;
    table_[i]->Resize(blockSize);
  }
  if (fe == nullptr) {
    
  }/* else {
    std::cout << " CONSTRUCTOR "<< std::endl;
    fe_ = fe;
    table_ = new Block<Clave>[tableSize];
    
    for (int i = 0; i < tableSize_; ++i)
      table_[i]->Resize(blockSize_);
    std::cout << " CONSTRUCTSSSSSSSSSSSSSSSSSOR "<< std::endl;
  }*/



  // table_.resize(tableSize_);

  //for (int i = 0; i < tableSize_; ++i){
  //  table_.at(i).Resize(blockSize_);
  //}
}

template <class Clave>
Tabla_hash_t<Clave>::~Tabla_hash_t(void){
  delete fd_;
  delete fe_;
  //delete[] table_;
}

template <class Clave>
bool Tabla_hash_t<Clave>::Buscar(Clave& X){

  bool encontrado = false;
  unsigned iter = 1;
  do{
    if(table_[fd_->operator()(X)]->Buscarc(X)){
      encontrado = true;
      sumar_intento();
    }else if(table_[fd_->operator()(X)]->EstaLleno()){
      encontrado = table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_]->Buscarc(X);
    }
    iter++;
    sumar_intento();
  }while(iter <= tableSize_ && !encontrado);

  return encontrado;
}

template <class Clave>
bool Tabla_hash_t<Clave>::Insertar(Clave& X){

  bool success = false;
  unsigned iter = 1;
  if(!Buscar(X) && !table_[fd_->operator()(X)]->EstaLleno()){
    success = table_[fd_->operator()(X)]->Insertarc(X);
    sumar_intento();
  }else if(table_[fd_->operator()(X)]->EstaLleno()){
    do{
      if(!table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_]->EstaLleno()){
        success = table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_]->Insertarc(X);
      } 
      iter++;
      sumar_intento();
    }while(iter <= tableSize_ && !success);
  }

  return success;
}

template <class Clave>
void Tabla_hash_t<Clave>::showTabla(void){
  for (int i = 0; i < tableSize_; ++i){
    std::cout << "[" << i << "]: ";
    for (int j = 0; j < table_[i]->get_self().size(); ++j){
      std::cout << table_[i]->at(j) << " ";
    }
    std::cout << std::endl;
  }
}

template <class Clave>
std::vector<Sequence<Clave>*>& Tabla_hash_t<Clave>::get_v(void){
  return table_;
}

template <class Clave>
void Tabla_hash_t<Clave>::change_fe(FuncionExploracion<Clave>* newfe){
  delete fe_;
  fe_ = newfe;
  intentos_ = 0;
}

template <class Clave>
int Tabla_hash_t<Clave>::get_intentos(void){
  return intentos_;
}

template <class Clave>
void Tabla_hash_t<Clave>::sumar_intento(void){
  intentos_++;
}

#endif