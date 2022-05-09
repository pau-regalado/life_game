#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>

#include "../include/NodoB.h"
#include "../include/AB.h"
#include "../include/ABE.h"

const int MAX_INT = 100;
const int MIN_INT = -1000;

void show_menu(void){
  std::cout << "OPCIONES: " << std::endl;
  std::cout << "d) Datos" << std::endl;
  std::cout << "i) Insertar" << std::endl;
  std::cout << "b) Buscar" << std::endl;
  std::cout << "m) Mostrar" << std::endl;
  std::cout << "s) Salir" << std::endl;

  std::cout << "Opción: ";
}

int main (int argc, char* argv[]){
  std::cout << std::endl;

  ABE<int> p;

  char opcion;
  int dato;
  bool quit = false;
  while (!quit){
    show_menu();
    std::cin >> opcion;
    switch(opcion){
      case 'i':
        std::cin >> dato;
        if (p.insertar(dato)) {
          std::cout << dato << " insertado!" << std::endl;
        }else{
          std::cout << dato << " ya esta!" << std::endl;
        }
        break;
      case 'd': 
        std::cout << "Tamaño: " << p.tam() << std::endl;
        std::cout << "Altura: " << p.alt() << std::endl;
        break;
      case 'b': 
        int x;
        std::cin >> x;
        if(p.buscar(x)){
          std::cout << x << " encontrado" << std::endl;
        }else{
          std::cout << x << " no encontrado" << std::endl;
        }
        break;
      case 'm':
        std::cout << p << std::endl;
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