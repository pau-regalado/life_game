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

template <class Key>
class Tabla_hash_t{

  public:
    Tabla_hash_t(unsigned tableSize = 0,
                 unsigned blockSize = 0,
                 FuncionDispersion<Key>* fd = nullptr,
                 FuncionExploracion<Key>* fe = nullptr);

    ~Tabla_hash_t(void);
    bool Buscar(Key& X);
    bool Insertar(Key& X);
    void showTabla(void);
    std::vector<Sequence<Key>*>& get_v(void);
    void change_fe(FuncionExploracion<Key>* newfe);

    // Mod
    void showTries();
  private:
    unsigned tableSize_;
    unsigned blockSize_;
    std::vector<Sequence<Key>*> table_;
    FuncionDispersion<Key>* fd_;
    FuncionExploracion<Key>* fe_;
};

// ----------------------------- IMPLEMENTATION -----------------------------

template <class Key>
Tabla_hash_t<Key>::Tabla_hash_t(unsigned tableSize,
                                  unsigned blockSize,
                                  FuncionDispersion<Key>* fd,
                                  FuncionExploracion<Key>* fe){
  tableSize_ = tableSize;
  fd_ = fd;
  blockSize_ = blockSize;
  
  table_.resize(tableSize);

  if (fe == nullptr) {
    for (int i = 0; i < tableSize_; ++i){
      table_[i] = new List<Key>;
      table_[i]->Resize(1);
    }
  } else {
    fe_ = fe;
    for (int i = 0; i < tableSize_; ++i){
      table_[i] = new Block<Key>;
      table_[i]->Resize(blockSize);
    }
  }
}

template <class Key>
Tabla_hash_t<Key>::~Tabla_hash_t(void){
  delete fd_;
  delete fe_;
}

template <class Key>
bool Tabla_hash_t<Key>::Buscar(Key& X){

  bool encontrado = false;
  unsigned iter = 1;
  do {
    if(table_[(*fd_)(X)]->Buscarc(X)){
      return true;
    }else if(!table_[(*fd_)(X)]->EstaLleno()){
      return false;
    } else {
      encontrado = table_[((*fd_)(X) + (*fe_)(X,iter))%tableSize_]->Buscarc(X);
    }
    iter++;
  } while(iter <= tableSize_ && !encontrado);

  return encontrado;
}

template <class Key>
bool Tabla_hash_t<Key>::Insertar(Key& X){

  bool success = false;
  unsigned iter = 1;
  if (Buscar(X)) {
    return false;
  }
  if (table_[(*fd_)(X)]->Insertarc(X)) {
    return true;
  } else {
    do{
      success = table_[((*fd_)(X) + (*fe_)(X,iter))%tableSize_]->Insertarc(X);
      iter++;
    }while(!success && iter <= tableSize_);
  }
  
  return success;
}

template <class Key>
void Tabla_hash_t<Key>::showTabla(void){
  for (int i = 0; i < tableSize_; ++i){
    std::cout << "[" << i << "]: ";
    table_[i]->print();
    std::cout << std::endl;
  }
}

template <class Key>
std::vector<Sequence<Key>*>& Tabla_hash_t<Key>::get_v(void){
  return table_;
}

template <class Key>
void Tabla_hash_t<Key>::change_fe(FuncionExploracion<Key>* newfe){
  delete fe_;
  fe_ = newfe;
}

template <class Key>
void Tabla_hash_t<Key>::showTries() {
  int capacidad = tableSize_ * blockSize_;
  float porcentaje = (table_[0]->getInsertElements() * 100) / float(capacidad);
  std::cout << "Capacidad tabla     : " << capacidad << std::endl;
  std::cout << "Elementos insertados: " << table_[0]->getInsertElements() << std::endl;
  std::cout << "Elementos buscados: " << table_[0]->getSearchElements() << std::endl;
  //std::cout << "Porcentaje ocupaod  : " << porcentaje << std::endl;
}

#endif