#include "../include/rejilla.h"
#include "../include/celula.h"

int main (void){
  Rejilla grid(5,5);

  grid.update();

  grid.printGrid();

  int opt;
  bool quit = false;
  while (!quit) {
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
    }
  }
  std::cout << std::endl;
  return 0;
}