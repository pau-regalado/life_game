#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>

#include "../include/nodo.h"
#include "../include/arbolb.h"
#include "../include/arbolbb.h"
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
  
  int i = 3;
  nodo<int>* x = new nodo<int>(i);
  arbolbb<int> b(x,i);
  b.busqueda_nivel(b.get_raiz(), 7);


  arbolb<int>* p = new arbolb<int>();

  char opcion;
  int dato;
  bool quit = false;
  while (!quit){
    show_menu();
    std::cin >> opcion;
    switch(opcion){
      case 'i':
        std::cin >> dato;
        p->insertar_equi(dato);
        break;
      case 'd': 
        std::cout << "tamaño: " << p->tam() << std::endl;
        std::cout << "altura: " << p->alt() << std::endl;
        break;
      case 'b': 
        int x;
        std::cin >> x;
        if(p->busqueda_nivel(p->get_raiz(), x)){
          std::cout<< "encontrado" << std::endl;
        }else{
          std::cout<< "NO encontrado" << std::endl;
        }
        break;
      case 'm':
        p->rec_niveles(p->get_raiz());
        break;
      case 's': 
        quit = true;
        break;
      default: std::cout << "opcion no soportada" << std::endl;
        break;
    }    
  }

  return 0;
}