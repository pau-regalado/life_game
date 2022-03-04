#include "../include/celula.h"
#include "../include/rejilla.h"

Celula::Celula(int x, int y, estado estado){
  x_ = x;
  y_ = y;
  estado_ = estado;
  vecinas_vivas_ = 0;
}

estado Celula::getState(void) const{
  return estado_;
}

void Celula::setState(const estado estado){
  estado_ = estado;
}

void Celula::setX(const int x){
  x_ = x;
}

void Celula::setY(const int y){
  y_ = y;
}

int Celula::getVivas(void){
  return vecinas_vivas_;
}

void Celula::updateState(void){
  if (estado_ == muerta && vecinas_vivas_ == 3){
    estado_ = viva;
  } else if (!(estado_ == viva && (vecinas_vivas_ == 3 || vecinas_vivas_ == 2))){
    estado_ = muerta;
  }
}

int Celula::neighbors(const Rejilla& g){
  vecinas_vivas_ = 
    g.getCelula(x_ - 1, y_ - 1).getState() +
    g.getCelula(x_ - 1, y_    ).getState() +
    g.getCelula(x_ - 1, y_ + 1).getState() +
    g.getCelula(x_    , y_ - 1).getState() +
    g.getCelula(x_    , y_ + 1).getState() +
    g.getCelula(x_ + 1, y_ - 1).getState() +
    g.getCelula(x_ + 1, y_    ).getState() +
    g.getCelula(x_ + 1, y_ + 1).getState() ;
  return vecinas_vivas_;
}

std::ostream& operator<<(std::ostream& os, const Celula& cell){
  if (cell.getState() == viva){
    os << "🔵";
  } else if (cell.getState() == muerta){
    os << "🔴";
  }
  return os;
}