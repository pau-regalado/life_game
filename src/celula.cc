#include "../include/celula.h"
#include "../include/rejilla.h"
#include "../include/state.h"

Celula::Celula(int x, int y,State* estado){
  x_ = x;
  y_ = y;
  vecinas_.resize(2);
  //vecinas_vivas_ = 0;

  if (estado == nullptr){
    estado_ = new StateDead(this);
  } else {
    estado_ = estado;
  }
}

Celula::~Celula(void){
  delete estado_;
  //estado_ = nullptr;
}

void Celula::clearVecinas(void){
  for (int i = 0; i < vecinas_.size(); i++)
    vecinas_[i] = 0;
}

State const * Celula::getState(void) const{
  return estado_;
}

std::vector<int>& Celula::getVecinas(void){
  return vecinas_;
}

void Celula::setState(State* estado){
  delete estado_;
  estado_ = estado;
}

void Celula::setX(const int x){
  x_ = x;
}

void Celula::setY(const int y){
  y_ = y;
}

int Celula::getX(void) const{
  return x_;
}

int Celula::getY(void){
  return y_;
}

int Celula::getVivas(void){
  // return vecinas_vivas_;
  return 0;
}

void Celula::updateState(void){
  // Cambia su estado por el que dicte su objeto estado
  estado_ = estado_->nextState();
}

void Celula::neighbors(const Grid& g){
/*
      vecinas_[g.getCelula(x_ - 1, y_ - 1).getState()]++;
      vecinas_[g.getCelula(x_ - 1, y_    ).getState()]++;
      vecinas_[g.getCelula(x_ - 1, y_ + 1).getState()]++;
      vecinas_[g.getCelula(x_    , y_ - 1).getState()]++;
      vecinas_[g.getCelula(x_    , y_ + 1).getState()]++;
      vecinas_[g.getCelula(x_ + 1, y_ - 1).getState()]++;
      vecinas_[g.getCelula(x_ + 1, y_    ).getState()]++;
      vecinas_[g.getCelula(x_ + 1, y_ + 1).getState()]++;
    return vecinas_vivas_;
*/
  estado_->neighbors(g, x_, y_);
}

std::ostream& operator<<(std::ostream& os, const Celula& cell){
  switch (cell.getState()->getState())
  {
  case A:
      return os << 'A';
    break;
  case D:
      return os << 'D';
    break;
  }
}