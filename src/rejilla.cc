#include "../include/rejilla.h"

Rejilla::Rejilla(int row, int col){

  nrows_ = row + 2;
  ncols_ = col + 2;
  turno_ = 0;

  rejilla_.resize(nrows_);
  for (int i = 0; i < nrows_; i++) {
    rejilla_[i].resize(ncols_);
  }

  for (int i = 0; i < nrows_; i++) {
    for (int j = 0; j < ncols_; j++) {
      rejilla_[i][j].setX(i);
      rejilla_[i][j].setY(j);
    }
  }
}

Rejilla::~Rejilla(){}

void Rejilla::update(void){
  int opt;
  bool quit = false;

  rejilla_[1][1].setState(viva);
  rejilla_[2][2].setState(viva);
  rejilla_[3][3].setState(viva);
  rejilla_[4][4].setState(viva);
  rejilla_[5][5].setState(viva);
  rejilla_[5][3].setState(viva);
  rejilla_[4][7].setState(viva);
  rejilla_[2][5].setState(viva);
  rejilla_[1][4].setState(viva);

  


  /*while (!quit) {
    std::cout << "1) Introducir celula viva" << std::endl;
    std::cout << "2) Terminar" << std::endl;
    std::cout << "opt> ";

    std::cin >> opt;

    std::cout << std::endl;

    switch (opt){
    case 1: {
      int x, y;
      std::cout << "x: ";
      std::cin >> x;
      std::cout << "y: ";
      std::cin >> y;

      if (x < nrows_ && y < ncols_)
        rejilla_[x][y].setState(viva);
      else
        std::cout << "Posicion invalida";
      std::cout << std::endl;
      break;
    }
    case 2: 
      quit = true;
    }
  }*/
}

const Celula& Rejilla::getCelula(int x, int y) const{
  return rejilla_[x][y];
}

void Rejilla::nextGeneration(void){

  // Actualizamos vecinas vivas
  for (int i = 1; i < nrows_ - 2; i++) {
    for (int j = 1; j < ncols_ - 2; j++) {
      rejilla_[i][j].neighbors(*this);
    }
  }

  for (int i = 1; i < nrows_ - 2; i++) {
    for (int j = 1; j < ncols_ - 2; j++) {
      rejilla_[i][j].updateState();
    }
  }

  turno_++;

  printGrid();

}

void Rejilla::printGrid(void){

  std::cout << std::endl << "TURNO: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 0; i < nrows_; i++) {
    std::cout << "⬛";
    for (int j = 0; j < ncols_; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}