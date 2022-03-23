#include "../include/rejilla.h"
#include "../include/celula.h"

int main (void){ 
  
  Grid* g = new GridWithOpenBorder(10,10);
  int opt;
  char type;
  bool quit = false;

  while (!quit) {
    std::cout << "Grid actual: " << g->getName() << " Size: " << g->getRow() << "x" << g->getCol() << std::endl;
    g->print();
    std::cout << "1) Introducir celulas vivas" << std::endl;
    std::cout << "2) Seleccionar Grid" << std::endl;
    std::cout << "3) NextGeneration" << std::endl;
    std::cout << "4) Rellenar con celulas" << std::endl;
    std::cout << "0) Salir" << std::endl;
    std::cout << "opt> ";

    std::cin >> opt;

    std::cout << std::endl;

    switch (opt){
    case 1: {
      g->insert();
      break;
    }
    case 2: {
      int x, y;
      delete g;
      std::cout << "Introduzca su nuevo tamaño: " << std::endl;
      std::cout << "Filas: ";
      std::cin >> x;
      std::cout << "Columnas: ";
      std::cin >> y;

      std::cout << "Nuevo tipo: ([O]pen | [P]eriodic | [R]eflective)" << std::endl;
      std::cout << "opt> ";

      std::cin >> type;

      std::cout << std::endl;

      switch (type){
      case 'O': {
        g = new GridWithOpenBorder(x,y);
        break;
      }
      case 'P': {
        g = new GridWithPeriodicBorder(x,y);
        break;
      }
      case 'R': {
        g = new GridWithReflectiveBorder(x,y);
        break;
      }
      default:
        g = new GridWithOpenBorder(x,y);
        break;
      }

      break;
    }
    case 3: {
      g->nextGeneration();
      break;
    }
    case 4: {
        g->defecto();
      break;
    }
    case 0:
      quit = true;
      break;
    }
  }
    if (g != nullptr){
      delete g;
    }
    return 0;
}


