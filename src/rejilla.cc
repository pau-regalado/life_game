#include "../include/rejilla.h"
#include "../include/celula.h"
#include "../include/state.h"

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

Rejilla::~Rejilla(){
  delete &rejilla_;
}

int Rejilla::getTurno(void){
  return turno_;
}

void Rejilla::defecto(void){
  rejilla_[1][1].setState(new StatePupa( &rejilla_[1][1]));
  rejilla_[2][2].setState(new StateLarva(&rejilla_[2][2]));
  rejilla_[3][3].setState(new StatePupa( &rejilla_[3][3]));
  rejilla_[4][4].setState(new StatePupa( &rejilla_[4][4]));
  rejilla_[4][3].setState(new StateLarva(&rejilla_[4][3]));
  rejilla_[2][4].setState(new StateAdult(&rejilla_[2][4]));
  rejilla_[1][4].setState(new StatePupa( &rejilla_[1][4]));
}

void Rejilla::update(void){
  int opt;
  bool quit = false;

  while (!quit) {
    std::cout << "1) Introducir celula viva" << std::endl;
    std::cout << "2) Terminar" << std::endl;
    std::cout << "opt> ";

    std::cin >> opt;

    std::cout << std::endl;

    switch (opt){
    case 1: {
      int x, y;
      char e;
      std::cout << "x: ";
      std::cin >> x;
      std::cout << "y: ";
      std::cin >> y;

      if (x < nrows_ - 1 && y < ncols_ - 1){
        std::cout << "En que estado? (D | E | L | P | A) : ";
        std::cin >> e;
        switch (e)
        {
        case 'D':
            rejilla_[x][y].setState(new StateDead(&rejilla_[x][y]));
          break;
        case 'E':
            rejilla_[x][y].setState(new StateEgg(&rejilla_[x][y]));
          break;        
        case 'L':
            rejilla_[x][y].setState(new StateLarva(&rejilla_[x][y]));
          break;
        case 'P':
            rejilla_[x][y].setState(new StatePupa(&rejilla_[x][y]));
          break;
        case 'A':
            rejilla_[x][y].setState(new StateAdult(&rejilla_[x][y]));
          break;
        default:
          break;
        }
      } else
        std::cout << "Posicion invalida";
      std::cout << std::endl;
      break;
    }
    case 2: 
      quit = true;
    }
  }
}

const Celula& Rejilla::getCelula(int x, int y) const{
  return rejilla_[x][y];
}

void Rejilla::nextGeneration(void){

  // Actualizamos vecinas vivas
  for (int i = 1; i < nrows_ - 1; i++) {
    for (int j = 1; j < ncols_ - 1; j++) {
      rejilla_[i][j].neighbors(*this);
    }
  }

  for (int i = 1; i < nrows_ - 1; i++) {
    for (int j = 1; j < ncols_ - 1; j++) {
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