#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <string.h>
#include <fstream>

#include "../include/nodo.h"
#include "../include/arbolb.h"
#include "nodo.cc"
#include "arbolb.cc"

const int MAX_INT = 100;
const int MIN_INT = -1000;

void show_menu(void){
  std::cout << "OPCIONES: " << std::endl;
  std::cout << "i) Insertar" << std::endl;
  std::cout << "d) Datos" << std::endl;
  std::cout << "b) Buscar" << std::endl;
  std::cout << "m) Mostrar" << std::endl;
  std::cout << "s) Salir" << std::endl;

  std::cout << "Opción: ";
}

int main (int argc, char* argv[]){
  std::cout << std::endl;
  

/*   nodo<int>* h = new nodo<int>(1);
  nodo<int>* w = new nodo<int>(2);
  //w->set_izq(h);
  nodo<int> e(3,h,w);
  nodo<int>* k = &e;

  arbolb<int> p(k);
  std::cout << p.es_vacio(p.get_raiz()) << std::endl;
  h->get_data();
  std::cout << k->get_izq()->get_data() << std::endl;
  
  std::cout << w->get_data() << std::endl;
  std::cout << p.es_hoja(k) << std::endl;

  p.rec_niveles(p.get_raiz());
  p.tam();
  std::cout << "tamaño es: " << p.tam() << std::endl;
  std::cout << "altura es: " << p.alt() << std::endl;
  if (p.equilibrado()){
    std::cout << "equilibrado:" << std::endl;
  }else{
    std::cout << "no equilibrado:" << std::endl;
  } */

  //arbolb<int>* p = new arbolb<int>;


  std::fstream filein(argv[1]);
  filein.open(argv[1],std::fstream::in);
  //file.open("./palabras.txt",std::ifstream::in);
  std::cout << filein.is_open() << std::endl;


  nodo<std::string>* nod = new nodo<std::string>("borrar","borrar");
  arbolb<std::string> p;
  p.set_raiz(nod);



  std::string dummy, dummy2;

  filein >> dummy;

  std::cout << "introduzco: " << dummy << std::endl;

  char opcion;
  int dato,clave, i = 5;
  bool quit = false;
  while (!quit){
    show_menu();
    std::cin >> opcion;
    switch(opcion){
      case 'i':
        //std::cout << "dato: ";
        //std::cin >> dato;
        std::cout << "clave: ";
        std::cin >> dummy;
        p.insertar(dummy);
        break;
      case 'd': 
        std::cout << "tamaño: " << p.tam() << std::endl;
        std::cout << "altura: " << p.alt() << std::endl;
        break;
      case 'b': 
        int x;
        std::cin >> dummy;
        if(p.buscar(dummy)!= nullptr){
          std::cout<< "encontrado" << std::endl;
        }else{
          std::cout<< "NO encontrado" << std::endl;
        }
        break;
      case 'm':
        p.rec_niveles(p.get_raiz());
        break;
      case 'e':
        std::cout << "clave: ";
        std::cin >> dummy;
        p.eliminar(dummy);
        break;

      case 'p':

        while (!filein.eof()){
          filein >> dummy;
          std::cout << "introduzco: " << dummy << std::endl;
          //std::cin >> dato; 
          p.insertar(dummy);
        }
        break;

      case 's': 
        quit = true;
        break;
      default: std::cout << "opcion no soportada" << std::endl;
        break;
    }    
  }


  filein.close();
  return 0;
}