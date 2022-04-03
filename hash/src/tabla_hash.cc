#include "../include/tabla_hash.h"

template <class Clave>
Tabla_hash_t<Clave>::Tabla_hash_t(FuncionDispersion<Clave>* fd,
                                  FuncionExploracion<Clave>* fe,
                                  unsigned nDatos, 
                                  unsigned nSinonimos){
  nDatos_ = nDatos;
  fd_ = fd;
  fe_ = fe;
  nSinonimos_ = nSinonimos;
  vDatos_.resize(nDatos_);

  for (int i = 0; i < nDatos_; ++i){
    vDatos_.at(i).Resize(nSinonimos_);
  }
  intentos_ = 0;
}

template <class Clave>
Tabla_hash_t<Clave>::~Tabla_hash_t(void){
  delete fd_;
  delete fe_;
}

template <class Clave>
bool Tabla_hash_t<Clave>::Buscar(Clave& X){

  bool encontrado = false;
  unsigned iter = 1;
  do{
    if(vDatos_.at(fd_->operator()(X)).Buscarc(X)){
      encontrado = true;
      sumar_intento();
    }else if(vDatos_.at(fd_->operator()(X)).EstaLleno()){
      encontrado = vDatos_.at((fd_->operator()(X) + fe_->operator()(X,iter))%nDatos_).Buscarc(X);
    }
    iter++;
    sumar_intento();
  }while(iter <= nDatos_ && !encontrado);

  return encontrado;
}

template <class Clave>
bool Tabla_hash_t<Clave>::Insertar(Clave& X){

  bool success = false;
  unsigned iter = 1;
  if(!Buscar(X) && !vDatos_.at(fd_->operator()(X)).EstaLleno()){
    success = vDatos_.at(fd_->operator()(X)).Insertarc(X);
    sumar_intento();
  }else if(vDatos_.at(fd_->operator()(X)).EstaLleno()){
    do{
      if(!vDatos_.at((fd_->operator()(X) + fe_->operator()(X,iter))%nDatos_).EstaLleno()){
        success = vDatos_.at((fd_->operator()(X) + fe_->operator()(X,iter))%nDatos_).Insertarc(X);
      } 
      iter++;
      sumar_intento();
    }while(iter <= nDatos_ && !success);
  }

  return success;
}

template <class Clave>
void Tabla_hash_t<Clave>::showTabla(void){
  for (int i = 0; i < nDatos_; ++i){
    std::cout << "[" << i << "]: ";
    for (int j = 0; j < nSinonimos_; ++j){
      std::cout << vDatos_.at(i).get_self().at(j) << " ";
    }
    std::cout << std::endl;
  }
}

template <class Clave>
std::vector<Lista_t<Clave>> Tabla_hash_t<Clave>::get_v(void){
  return vDatos_;
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
    if (vDatos_.at(fd_->operator()(X)).Buscarc(X)){
      encontrado = true;
    }else if(vDatos_.at(fd_->operator()(X)).EstaLleno()){
      
      
        std::cout << "Se va a buscar en "<< fd_->operator()(X) +fe_->operator()(X,iter) << std::endl;
        encontrado = vDatos_.at((fd_->operator()(X) +fe_->operator()(X,iter))%nDatos_).Buscarc(X);
        std::cout << "Se ha encontrado? "<< encontrado << std::endl;
        
        std::cout << "EL siguiente esta lleno? "<< vDatos_.at((fd_->operator()(X) +fe_->operator()(X,iter+1))%nDatos_).EstaLleno() << std::endl;
        std::cout << "Miro si en "<< (fd_->operator()(X) +fe_->operator()(X,iter+1))%nDatos_ << " se puede meter" << std::endl;
        
 */