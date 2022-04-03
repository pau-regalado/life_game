#include <iostream>
#include <array>

// Ficheros de cabecera

#include "../include/tabla_hash.h"
//#include "../include/funcion_dispersion.h"
//#include "../include/lista_t.h"

#include "../src/lista_t.cc"
#include "../src/tabla_hash.cc"

template <class Clave>
void probar_tabla(Tabla_hash_t<Clave>* t){
  Clave n;
  for (int i = 0; i < 20; ++i ){
    n = std::rand();
    t->Insertar(n);
  }
} 


void showmenu(void){
  std::cout << "i) Insertar elemento" << std::endl;
  std::cout << "b) Buscar elemento" << std::endl;
  std::cout << "m) mostrar tabla" << std::endl;
  std::cout << "l) Esta lleno?" << std::endl;
  std::cout << "q) Salir" << std::endl;
  std::cout << "Introduzca una opcion: ";
}

void pedir_disp(char& op){

  std::cout << "Tipo de funcion de exploracion? " << std::endl;
  std::cout << "l) lineal " << std::endl;
  std::cout << "c) cuadratica " << std::endl;
  std::cout << "d) doble dispersion " << std::endl;
  std::cout << "r) redispersion " << std::endl;

  std::cout << "Introduzca una opcion: ";
  std::cin >> op;
  std::cout << std::endl;
}


int main (int argc, char* argv[]){

  int tamano, tamcelda;
  char tipo;
  bool prueba = false;

// ---------------------- PIDE F DISPERSION ---------------

  std::cout << "Bienvenido, introduzca el tamaño de la tabla:" << std::endl;
  std::cout << "Tamaño de la tabla: ";
  std::cin >> tamano;

  std::cout << "Tamaño de la celda: ";
  std::cin >> tamcelda;

  std::cout << std::endl;

  std::cout << "Tipo de funcion de dispersion? " << std::endl;
  std::cout << "m) modulo " << std::endl;
  std::cout << "r) random " << std::endl;
  std::cout << "p) prueba " << std::endl;
  std::cout << "Introduzca una opcion: ";
  std::cin >> tipo;
  std::cout << std::endl;

  FuncionDispersion<int>* fd;

  switch (tipo){
    case 'm': fd = new fdModulo<int>(tamano);
      break;
    case 'r': fd = new fdrandom<int>(tamano);
      break;
    case 'p': prueba = true;
      break;
    default:
     std::cout << "Error" << std::endl;
  }

// ---------------------- PIDE F EXPLORACION ---------------
  if (!prueba) { 
    FuncionExploracion<int>* fe;
    FuncionDispersion<int>* fdp;
    pedir_disp(tipo);

    switch (tipo){
      case 'l': fe = new feLineal<int>;
        break;
      case 'c': fe = new feCuadratica<int>;
        break;
      case 'd': fe = new feDobleDispersion<int>(fd);
        break;
      case 'r': 
      fdp = new fdrandom<int> (tamano);
      fe = new feRedispersion<int>(fdp);
        break;
      default: 
        std::cout << "Error" << std::endl;
    }

  // ---------------------- CREA TABLA ---------------

    Tabla_hash_t<int> tabla(fd,fe,tamano,tamcelda);

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
          if (tabla.Insertar(tamano)){
            std::cout << "Se almaceno " << tamano << " correctamente" << std::endl;
          }else{
            std::cout << "No se pudo insertar. " << tamano << std::endl;
          }
          break;
        
        case 'b': 
          std::cout << "Numero a buscar: ";
          std::cin >> tamano;
          if (tabla.Buscar(tamano)){
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
          if (tabla.get_v().at(tamano).EstaLleno()){
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
  }else{
    int size = 10, nsim = 3, X = 10; 
    FuncionExploracion<int>* fe;
    FuncionDispersion<int>* fd = new fdModulo<int> (size);

    // Prueba fe lineal
    fe = new feLineal<int>;
    Tabla_hash_t<int>* t_prueba = new Tabla_hash_t<int>(fd,fe,size,nsim);

    probar_tabla(t_prueba);
    std::cout << "Con exploracion lineal: " << t_prueba->get_intentos() << std::endl;

    // Prueba feCuadratica
    fe = new feCuadratica<int>;
    t_prueba = new Tabla_hash_t<int>(fd,fe,size,nsim);
    //t_prueba->change_fe(fe);
  
    probar_tabla(t_prueba);
    std::cout << "Con exploracion cuadratica: " << t_prueba->get_intentos() << std::endl;

    // Prueba feDobleDispersion
    fe = new feDobleDispersion<int>(fd);
    t_prueba = new Tabla_hash_t<int>(fd,fe,size,nsim);
    //t_prueba->change_fe(fe);
    probar_tabla(t_prueba);
    std::cout << "Con exploracion dobledispersion: " << t_prueba->get_intentos() << std::endl;


    // prueba redisp
    fd = new fdrandom<int> (size);
    fe = new feRedispersion<int>(fd);
   t_prueba = new Tabla_hash_t<int>(fd,fe,size,nsim);
    //t_prueba->change_fe(fe);
    probar_tabla(t_prueba);
    std::cout << "Con exploracion dredispersion: " << t_prueba->get_intentos() << std::endl;

  }
  
  return 0;
}