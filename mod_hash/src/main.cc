#include <iostream>
#include <array>

// Ficheros de cabecera

#include "../include/tabla_hash.h"
#include "../include/sequence.h"
#include "../include/list.h"
#include "../include/block.h"
#include "../include/funcion_dispersion.h"
#include "../include/funcion_exploracion.h"


class Clave {
  public:
    Clave(long clave, int cont = 0): clave_(clave), contador_(cont){}
    bool operator==(Clave& other){
      return clave_ == other.getClave();
    }
    bool operator==(int other){
      return clave_ == other;
    }
    long operator+(Clave& other){
      return clave_ + other.getClave();
    }
    long operator+(int other){
      return clave_ + other;
    }

    std::ostream& operator<<(std::ostream& os){
      os << clave_;
      return os;
    }

    long getClave(){return clave_;}
    void addCont(){contador_++;}
    void resetCont(){contador_ = 0;}
  private:
    long clave_;
    int contador_;
};

// "Sobrecarga del operador"
Clave& Long(long x){
  Clave aux(x);
  return aux;
}

void showmenu(void){
  std::cout << "i) Insertar elemento" << std::endl;
  std::cout << "b) Buscar elemento" << std::endl;
  std::cout << "m) mostrar tabla" << std::endl;
  std::cout << "l) Esta lleno?" << std::endl;
  std::cout << "q) Salir" << std::endl;
  std::cout << "Introduzca una opcion: ";
}

void pedir_exp(char& op){

  std::cout << "Tipo de funcion de exploracion? " << std::endl;
  std::cout << "l) lineal " << std::endl;
  std::cout << "c) cuadratica " << std::endl;
  std::cout << "d) doble dispersion " << std::endl;
  std::cout << "r) redispersion " << std::endl;
  std::cout << "s) sin exploracion (disp. abierta) " << std::endl;

  std::cout << "Introduzca una opcion: ";
  std::cin >> op;
  std::cout << std::endl;
}


int main (int argc, char* argv[]){

  int tamano, tamcelda;
  char tipo;

// ---------------------- PIDE F DISPERSION ---------------

  std::cout << "Bienvenido, introduzca el tamaño de la tabla:" << std::endl;
  std::cout << "Tamaño de la tabla: ";
  std::cin >> tamano;

  std::cout << "Tamaño de la celda: ";
  std::cin >> tamcelda;

  std::cout << std::endl;

  std::cout << "Tipo de funcion de dispersion? " << std::endl;
  std::cout << "m) modulo " << std::endl;
  std::cout << "s) suma " << std::endl;
  std::cout << "r) random " << std::endl;
  std::cout << "Introduzca una opcion: ";
  std::cin >> tipo;
  std::cout << std::endl;

  FuncionDispersion<Clave>* fd;

  switch (tipo){
    case 'm': fd = new fdModulo<Clave>(tamano);
      break;
    case 'r': fd = new fdrandom<Clave>(tamano);
      break;
    case 's': fd = new fdSuma<Clave>(tamano);
      break;
    default:
     std::cout << "Error" << std::endl;
  }

// ---------------------- PIDE F EXPLORACION ---------------

    FuncionExploracion<Clave>* fe;
    FuncionDispersion<Clave>* fdp;
    pedir_exp(tipo);

    switch (tipo){
      case 'l': fe = new feLineal<Clave>;
        break;
      case 'c': fe = new feCuadratica<Clave>;
        break;
      case 'd': fe = new feDobleDispersion<Clave>(fd);
        break;
      case 'r': 
        fdp = new fdrandom<Clave> (tamano);
        fe = new feRedispersion<Clave>(fdp);
        break;
      case 's': fe = nullptr;
        break;
      default: 
        std::cout << "Error" << std::endl;
    }

  // ---------------------- CREA TABLA ---------------

    Tabla_hash_t<Clave> tabla(tamano, tamcelda, fd, fe);
    std::vector<Clave> bank;
    int bankSize = tamano * tamcelda;

    for (int i = 0; i < bankSize; i++) {
      bank.push_back(Long(rand()));
    }

    for (int i = 0; i < bankSize / 2; i++) {
      tabla.Insertar(bank[i]);
    }

    for (int i = (bankSize / 2) + 1; i < bankSize; i++) {
      if (tabla.Buscar(bank[i])) {
         // acceder al metodo addCont de la Clave que se encontro 
      } 
    }

    bool quit = false;
    while(!quit){

      showmenu();
      std::cin >> tipo;
      std::cout << std::endl;
      switch (tipo){
        case 'i':
          std::cout << "Numero a insertar: ";
          std::cin >> tamano;
          std::cout << "insertando " << tamano << " ..." << std::endl;
          if (tabla.Insertar(Long(tamano))){
            std::cout << "Se almaceno " << tamano << " correctamente" << std::endl;
          }else{
            std::cout << "No se pudo insertar. " << tamano << std::endl;
          }
          break;
        
        case 'b': 
          std::cout << "Numero a buscar: ";
          std::cin >> tamano;
          if (tabla.Buscar(Long(tamano))){
            std::cout << tamano << " esta almacenado" << std::endl;
          }else{
            std::cout << tamano << " no esta almacenado" << std::endl;
          }
          break;

        case 'm': 
          tabla.showTabla();
          break;

        case 'l': 
          std::cout << "fila vacia?: ";
          std::cin >> tamano;
          if (tabla.get_v()[tamano]->EstaLleno()){
            std::cout << "Esta llena" << std::endl;
          }else{
            std::cout << "No esta llena" << std::endl;
          }
          break;

        case 'q':
          std::cout << "Adios" << std::endl;
          quit = true;
          break;

        default: std::cout << "Error. Vuelva a introducir la opcion" << std::endl;
      }
    }
 
  return 0;
}