#include "../include/rejilla.h"
#include "../include/celula.h"

int main (void){  

  int r, c, i, n; 

  std::cout << "Filas: ";
  std::cin >> r;
  std::cout << std::endl;

  std::cout << "Columnas: ";
  std::cin >> c;
  std::cout << std::endl;

  Rejilla grid(r,c);

  std::cout << "Iniciar por defecto?: 1 Si | 0 No : ";
  std::cin >> i;
  std::cout << std::endl;

  if (i){
    grid.defecto();
  } else {
    grid.update();
  }

  std::cout << std::endl  << "Numero maximo de iteraciones: ";
  std::cin >> n;
  std::cout << std::endl;

  grid.printGrid();

  int opt;
  bool quit = false;
  while (!quit && grid.getTurno() < n) {
    std::cout << "1) Continuar" << std::endl;
    std::cout << "2) Terminar" << std::endl;
    std::cout << "opt> ";

    std::cin >> opt;

    std::cout << std::endl;

    switch (opt){
    case 1: {
      grid.nextGeneration();
      break;
    }
    case 2: 
      quit = true;
      break;
    default: 
        quit = true;
    }
  }
  std::cout << std::endl;
  return 0;
}