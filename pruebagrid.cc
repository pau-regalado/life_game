#include <iostream>
#include <vector>

class Grid{
  protected:
    int turno_;
    int nrows_, ncols_;
    std::vector<std::vector<int>> rejilla_;

  public:
    // Grid(int row = defSize, int col = defSize);
    virtual ~Grid() = 0;
    virtual void saludar() = 0;
    virtual void print() = 0;
    friend std::ostream& operator<<(std::ostream& os, Grid &g);
};

std::ostream& operator<<(std::ostream& os, Grid &g) {
  g.print();
  return os;
}

Grid::~Grid(){std::cout << "adios base" << std::endl;}
/*
std::ostream& operator<<(std::ostream& os, Grid &g){
  std::cout << std::endl << "TURNO BASE: " << g.turno_ << std::endl;

  for (int i = 0; i < g.ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 0; i < g.nrows_ + 2; i++) {
    std::cout << "⬛";
    for (int j = 0; j < g.ncols_ + 2; j++) {
      std::cout << g.rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < g.ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}
*/
class GridWithOpenBorder: public Grid{
  public:
    GridWithOpenBorder(int row, int col);
    ~GridWithOpenBorder(){std::cout << "adios hija" << std::endl;}

    virtual void saludar(){std::cout << "hola derivada" << std::endl;}

    virtual void print();
    // std::ostream& operator<<(std::ostream& os,  GridWithOpenBorder &g);
    //std::ostream& operator<<(std::ostream& os) override;
};
/*
std::ostream& Grid::operator<<(std::ostream& os){
  std::cout << std::endl << "TURNO: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 0; i < nrows_ + 2; i++) {
    std::cout << "⬛";
    for (int j = 0; j < ncols_ + 2; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}
*/
GridWithOpenBorder::GridWithOpenBorder(int row, int col){
  nrows_ = row;
  ncols_ = col;
  turno_ = 0;

  rejilla_.resize(nrows_ + 2);

  for (int i = 0; i < nrows_ + 2; i++) {
    rejilla_[i].resize(ncols_  + 2);
  }

  for (int i = 0; i < nrows_  + 2; i++) {
    for (int j = 0; j < ncols_  + 2; j++) {
      if (i == 0 || j == 0 || i == nrows_ + 1 || j == ncols_ + 1) {
        rejilla_[i][j] = 0;
      } else {
        rejilla_[i][j] = i;
      }
    }
  } 
}
/*
std::ostream& GridWithOpenBorder::operator<<(std::ostream& os){
  os << std::endl << "TURNO: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    os << "⬛";
  }
  os << std::endl;

  for (int i = 0; i < nrows_ + 2; i++) {
    os << "⬛";
    for (int j = 0; j < ncols_ + 2; j++) {
      os << rejilla_[i][j];
    }
    os << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    os << "⬛";
  }
  os << std::endl << std::endl;
  return os;
}
*/
/*
std::ostream& operator<<(std::ostream& os, GridWithOpenBorder &g){
  std::cout << std::endl << "TURNO OPEN: " << g.turno_ << std::endl;

  for (int i = 0; i < g.ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 0; i < g.nrows_ + 2; i++) {
    std::cout << "⬛";
    for (int j = 0; j < g.ncols_ + 2; j++) {
      std::cout << g.rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < g.ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}
*/

void GridWithOpenBorder::print(void){
  std::cout << std::endl << "TURNO OPEN: " << turno_ << std::endl;

  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl;

  for (int i = 0; i < nrows_ + 2; i++) {
    std::cout << "⬛";
    for (int j = 0; j < ncols_ + 2; j++) {
      std::cout << rejilla_[i][j];
    }
    std::cout << "⬛" << std::endl;
  }
  
  for (int i = 0; i < ncols_ + 2; i++){
    std::cout << "⬛";
  }
  std::cout << std::endl << std::endl;
}

int main (void) {

  Grid* g = new GridWithOpenBorder(4,4);

  std::cout << *g << std::endl;

  delete g;
  return 0;
}