#include "../include/rejilla.h"
#include "../include/celula.h"
#include "../include/state.h"

// ----------------------- Grid ---------------------------------

Grid::Grid(int row, int col){
  nrows_ = row;
  ncols_ = col;
  turno_ = 0;

  rejilla_ = new Celula*[nrows_ + 2];
  for (int i = 0; i < nrows_ + 2; i++) {
    rejilla_[i] = new Celula[ncols_ + 2];
    for (int j = 0; j < ncols_ + 2; j++) {
//     if (i == 0 || j == 0 || i == nrows_ + 1 || j == ncols_ + 1) {
      rejilla_[i][j].setX(i);
      rejilla_[i][j].setY(j);
      rejilla_[i][j].setState(new StateDead(&rejilla_[i][j]));
    }
  } 
}

std::ostream& operator<<(std::ostream& os, Grid &g) {
  g.print();
  return os;
}

Grid::~Grid(){std::cout << "Destruccion base" << std::endl;}

void Grid::defecto(void){

  rejilla_[1][1].setState(new StateAlive(&rejilla_[1][1]));
  rejilla_[1][2].setState(new StateAlive(&rejilla_[1][2]));
  rejilla_[1][3].setState(new StateAlive(&rejilla_[1][3]));
  //rejilla_[4][1].setState(new StateAlive(&rejilla_[4][1]));

  //rejilla_[4][3].setState(new StateAlive(&rejilla_[4][3]));
  //rejilla_[2][4].setState(new StateAlive(&rejilla_[2][4]));
  //rejilla_[1][4].setState(new StateAlive(&rejilla_[1][4]));

/*
  rejilla_[1][1].setState(new StateAlive(&rejilla_[1][1]));
  rejilla_[2][2].setState(new StateAlive(&rejilla_[2][2]));
  rejilla_[3][3].setState(new StateAlive(&rejilla_[3][3]));
  rejilla_[4][4].setState(new StateAlive(&rejilla_[4][4]));
  //rejilla_[4][3].setState(new StateAlive(&rejilla_[4][3]));
  //rejilla_[2][4].setState(new StateAlive(&rejilla_[2][4]));
  //rejilla_[1][4].setState(new StateAlive(&rejilla_[1][4]));*/

}

void Grid::insert(void){
  std::cout << "Grid actual:" << std::endl;
  print();

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

      if (x < nrows_ + 1 && y < ncols_ + 1){
        std::cout << "En que estado? (D | A) : ";
        std::cin >> e;
        switch (e)
        {
        case 'D':
            rejilla_[x][y].setState(new StateDead(&rejilla_[x][y]));
          break;
        case 'A':
            rejilla_[x][y].setState(new StateAlive(&rejilla_[x][y]));
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

void Grid::nextGeneration(void){

  // Actualizamos vecinas vivas
  for (int i = 1; i < nrows_ + 1; i++) {
    for (int j = 1; j < ncols_ + 1; j++) {
      rejilla_[i][j].neighbors(*this);
    }
  }
  for (int i = 1; i < nrows_ + 1; i++) {
    for (int j = 1; j < ncols_ + 1; j++) {
      rejilla_[i][j].updateState();
    }
  }
  turno_++;
  print();
}

// ------------------- GridWithOpenBorder ---------------------------------

GridWithOpenBorder::GridWithOpenBorder(int row, int col): Grid(row,col){}

GridWithOpenBorder::~GridWithOpenBorder(){
  std::cout << "Destruccion OpenBorder" << std::endl;

  for (int i = 0; i < nrows_ + 2; i++) {
    for (int j = 0; j < ncols_ + 2; j++) {
      rejilla_[i][j];
    }
  }
  delete rejilla_;
}

Celula& GridWithOpenBorder::getCelula(int x, int y){

  //if (x == 0 || y == 0 || x == nrows_ + 1 || y == ncols_ + 1) {
    return rejilla_[x][y];
  //}
  
}
const Celula& GridWithOpenBorder::getCelula(int x, int y) const{
  return rejilla_[x][y];
}

void GridWithOpenBorder::print(void){
  std::cout << std::endl << "TURNO OPEN: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 1; i < nrows_ + 1; i++) {
    std::cout << "⬛";
    for (int j = 1; j < ncols_ + 1; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}

// ------------------- GridWithPeriodicBorder ---------------------------------

GridWithPeriodicBorder::GridWithPeriodicBorder(int row, int col): Grid(row,col){}

GridWithPeriodicBorder::~GridWithPeriodicBorder(){
  std::cout << "Destruccion PeriodicBorder" << std::endl;
  for (int i = 0; i < nrows_; i++) {
    for (int j = 0; j < ncols_; j++) {
      rejilla_[i][j];
    }
  }
  delete rejilla_;
}

Celula& GridWithPeriodicBorder::getCelula(int x, int y){
  //std::cout << "entra: i " << x << " y " << y << std::endl;
  if (x == 0) {
    x = nrows_;
  }else if (x == nrows_ + 1) {
    x = 0;
  }
  if (y == 0) {
    y = ncols_;
  }else if (y == ncols_ + 1) {
    y = 0;
  }

  //std::cout << "sale: i " << x << " y " << y << std::endl;
  return rejilla_[x][y];
}
const Celula& GridWithPeriodicBorder::getCelula(int x, int y) const{
  //std::cout << "entra: i " << x << " y " << y << std::endl;
  if (x == 0) {
    x = nrows_;
  }else if (x == nrows_ + 1) {
    x = 1;
  }
  if (y == 0) {
    y = ncols_;
  }else if (y == ncols_ + 1) {
    y = 1;
  }
  //std::cout << "sale: i " << x << " y " << y << std::endl;
  return rejilla_[x][y];
}

void GridWithPeriodicBorder::print(void){
  std::cout << std::endl << "TURNO PERIODIC: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 1; i < nrows_ + 1; i++) {
    std::cout << "⬛";
    for (int j = 1; j < ncols_ + 1; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}

// ------------------- GridWithReflectiveBorder ---------------------------------


GridWithReflectiveBorder::GridWithReflectiveBorder(int row, int col){
  nrows_ = row;
  ncols_ = col;
  turno_ = 0;

  rejilla_ = new Celula*[nrows_ + 2];
  for (int i = 0; i < nrows_ + 2; i++) {
    rejilla_[i] = new Celula[ncols_ + 2];
    for (int j = 0; j < ncols_ + 2; j++) {
      rejilla_[i][j].setX(i);
      rejilla_[i][j].setY(j);
      rejilla_[i][j].setState(new StateDead(&rejilla_[i][j]));
    }
  }
} 

/*
      if (i == 0) {
        rejilla_[i][j].setX(i+1);
      }else if (i == nrows_ + 1){
        rejilla_[i][j].setX(i-1);
      } 
      if (j == 0) {
        rejilla_[i][j].setY(j+1);
      }else if (j == ncols_ + 1){
        rejilla_[i][j].setY(j-1);
      }
*/


GridWithReflectiveBorder::~GridWithReflectiveBorder(){
  std::cout << "Destruccion ReflectiveBorder" << std::endl;

  for (int i = 0; i < nrows_ + 2; i++) {
    for (int j = 0; j < ncols_ + 2; j++) {
      rejilla_[i][j];
    }
  }
  delete rejilla_;
}

Celula& GridWithReflectiveBorder::getCelula(int x, int y){
  if (x == 0){
    x = 1;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (x == nrows_ + 1){
    x = nrows_;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (y == 0){
    y = 1;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  if (y == ncols_ + 1){
    y = ncols_;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  return rejilla_[x][y];
}
const Celula& GridWithReflectiveBorder::getCelula(int x, int y) const{
  if (x == 0){
    x = 1;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (x == nrows_ + 1){
    x = nrows_;
    if (y == 0) {
      y = 1;
    } else if (y == ncols_ + 1) {
      y = ncols_;
    }
  }
  if (y == 0){
    y = 1;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  if (y == ncols_ + 1){
    y = ncols_;
    if (x == 0) {
      x = 1;
    } else if (x == nrows_ + 1) {
      x = nrows_;
    }
  }
  return rejilla_[x][y];
}

void GridWithReflectiveBorder::print(void){
  std::cout << std::endl << "TURNO Reflective: " << turno_ << std::endl;
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 1; i < nrows_ + 1; i++) {
    std::cout << "⬛";
    for (int j = 1; j < ncols_ + 1; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}
