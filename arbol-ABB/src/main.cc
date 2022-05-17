#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>

#include "../include/NodoB.h"
#include "../include/AB.h"
#include "../include/ABE.h"
#include "../include/ABB.h"

const int MAX_INT = 100;
const int MIN_INT = -1000;

void show_menu(char & o) {
  std::cout << "──────────────────────────" << std::endl;
  std::cout << "OPCIONES: " << std::endl;
  std::cout << "f) Datos" << std::endl;
  std::cout << "i) Insertar" << std::endl;
  std::cout << "b) Buscar" << std::endl;
  std::cout << "m) Mostrar" << std::endl;
  std::cout << "c) Cambiar arbol" << std::endl;
  std::cout << "s) Salir" << std::endl;

  std::cout << "Opción: ";
  std::cin >> o;
  std::cout << "──────────────────────────" << std::endl;
}

template <class Key>
void changeTree(AB<Key>* &arbol, char &actArbol) {
  char prevArbol = actArbol;
  std::cout << "────────────────────────────" << std::endl;
  std::cout << "i) Equ[i]librado" << std::endl;
  std::cout << "b) [b]usqueda" << std::endl;
  std::cout << "Seleccione un arbol: ";
  std::cin >> actArbol;
  std::cout << "────────────────────────────" << std::endl;

  if (prevArbol != actArbol) {
    delete arbol;
    switch (actArbol) {
      case 'i':
        arbol = new ABE<Key>;
        std::cout << "Ahora ABE" << std::endl;
        break;
      case 'b':
        arbol = new ABB<Key>;
        std::cout << "Ahora ABB" << std::endl;
        break;
      default:
        actArbol = 'b';
        arbol = new ABB<Key>;
        std::cout << "Ahora ABB" << std::endl;
        break;
    }
  } else {
    actArbol = prevArbol;
    std::cout << "El arbol ya es de ese tipo, abortando..." << std::endl;
  }
}

int main (int argc, char* argv[]){
  AB<int>* arbol;
  
  char arbolType;
  changeTree(arbol, arbolType);

  char opcion;
  bool quit = false;
  while (!quit){
    show_menu(opcion);
    switch(opcion){
      case 'i': {
        int dato;
        std::cout << "Dato a insertar: ";
        std::cin >> dato;
        if (arbol->insertar(dato)) {
          std::cout << dato << " insertado!" << std::endl << *arbol << std::endl;
        }else{
          std::cout << dato << " ya esta!" << std::endl;
        }
        break;
      }
      case 'f': 
        std::cout << "Tamaño: " << arbol->tam() << std::endl;
        std::cout << "Altura: " << arbol->alt() << std::endl;
        break;
      case 'b': {
        int x;
        std::cout << "Dato a buscar: ";
        std::cin >> x;
        if(arbol->buscar(x)){
          std::cout << x << " encontrado" << std::endl << *arbol << std::endl;
        }else{
          std::cout << x << " no encontrado" << std::endl;
        }
        break;
      }
      case 'd': {
        int x;
        std::cout << "Dato a eliminar: ";
        std::cin >> x;
        if(arbol->eliminar(x)){
          std::cout << x << " borrado" << std::endl << *arbol << std::endl;
        }else{
          std::cout << x << " no se ha podido borrar" << std::endl;
        }
        break;
      }
      case 'c': {
        changeTree(arbol, arbolType);
        break;
      }
      case 'm':
        std::cout << *arbol << std::endl;
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