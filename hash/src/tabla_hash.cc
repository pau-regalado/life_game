#include "../include/tabla_hash.h"
#include "../include/list.h"
#include "../include/block.h"

template <class Clave>
Tabla_hash_t<Clave>::Tabla_hash_t(unsigned tableSize,
                                  unsigned blockSize,
                                  FuncionDispersion<Clave>* fd,
                                  FuncionExploracion<Clave>* fe){
  tableSize_ = tableSize;
  fd_ = fd;
  blockSize_ = blockSize;
  intentos_ = 0;
  
  if (fe == nullptr) {
    table_ = new List<Clave>[tableSize];
  } else {
    std::cout << " CONSTRUCTOR "<< std::endl;
    fe_ = fe;
    table_ = new Block<Clave>[tableSize];
    
    for (int i = 0; i < tableSize_; ++i)
      table_[i].Resize(blockSize_);
    std::cout << " CONSTRUCTSSSSSSSSSSSSSSSSSOR "<< std::endl;
  }



  // table_.resize(tableSize_);

  //for (int i = 0; i < tableSize_; ++i){
  //  table_.at(i).Resize(blockSize_);
  //}
}

template <class Clave>
Tabla_hash_t<Clave>::~Tabla_hash_t(void){
  delete fd_;
  delete fe_;
  delete[] table_;
}

template <class Clave>
bool Tabla_hash_t<Clave>::Buscar(Clave& X){

  bool encontrado = false;
  unsigned iter = 1;
  do{
    if(table_[fd_->operator()(X)].Buscarc(X)){
      encontrado = true;
      sumar_intento();
    }else if(table_[fd_->operator()(X)].EstaLleno()){
      encontrado = table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_].Buscarc(X);
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
  if(!Buscar(X) && !table_[fd_->operator()(X)].EstaLleno()){
    success = table_[fd_->operator()(X)].Insertarc(X);
    sumar_intento();
  }else if(table_[fd_->operator()(X)].EstaLleno()){
    do{
      if(!table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_].EstaLleno()){
        success = table_[(fd_->operator()(X) + fe_->operator()(X,iter))%tableSize_].Insertarc(X);
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
    for (int j = 0; j < blockSize_; ++j){
      std::cout << table_[i].get_self()[j] << " ";
    }
    std::cout << std::endl;
  }
}

template <class Clave>
Sequence<Clave>* Tabla_hash_t<Clave>::get_v(void){
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





/*  VIEJO BUSCAR
  bool encontrado = false;
  std::cout << "Se busco en "<< fd_->operator()(X) << std::endl;
  std::cout << "Y luego se va a buscar en "<< fd_->operator()(X) +fe_->operator()(X,1) << std::endl;
unsigned iter = 1;
  do{
    if (table_.at(fd_->operator()(X)).Buscarc(X)){
      encontrado = true;
    }else if(table_.at(fd_->operator()(X)).EstaLleno()){
      
      
        std::cout << "Se va a buscar en "<< fd_->operator()(X) +fe_->operator()(X,iter) << std::endl;
        encontrado = table_.at((fd_->operator()(X) +fe_->operator()(X,iter))%tableSize_).Buscarc(X);
        std::cout << "Se ha encontrado? "<< encontrado << std::endl;
        
        std::cout << "EL siguiente esta lleno? "<< table_.at((fd_->operator()(X) +fe_->operator()(X,iter+1))%tableSize_).EstaLleno() << std::endl;
        std::cout << "Miro si en "<< (fd_->operator()(X) +fe_->operator()(X,iter+1))%tableSize_ << " se puede meter" << std::endl;
        
 */