#include "../include/state.h"
#include "../include/rejilla.h"
#include "../include/celula.h"

// StateDead -------------------------------------------------

int StateDead::neighbors(const Grid& grid, int i, int j ) {

  nVivas = 0;

  celula_->clearVecinas(); // Reseteamos las vecinas
  celula_->vecinas_[grid.getCelula(i - 1, j - 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i - 1, j    ).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i - 1, j + 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i    , j - 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i    , j + 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i + 1, j - 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i + 1, j    ).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i + 1, j + 1).getState()->getState()]++;
  return nVivas;
}

State* StateDead::nextState(){
  
  if (celula_->vecinas_[A] == 3){
    std::cout << "vive " << celula_->getX() << " " << celula_->getY() << std::endl;
    return new StateAlive(celula_);
  } else {
    return new StateDead(celula_);
  }
}

estado StateDead::getState() const{
    return D;
}

// StateAlive -------------------------------------------------

int StateAlive::neighbors(const Grid& grid, int i, int j ) {
    /*Calcula el numero de larvas y el de huevos, retorna la resta
    para luego comprobar si es prositivo => muerta: larva*/
  celula_->clearVecinas(); // Reseteamos las vecinas
  // Modifica el vector de vecinas de su celula 

  celula_->vecinas_[grid.getCelula(i - 1, j - 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i - 1, j    ).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i - 1, j + 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i    , j - 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i    , j + 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i + 1, j - 1).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i + 1, j    ).getState()->getState()]++;
  celula_->vecinas_[grid.getCelula(i + 1, j + 1).getState()->getState()]++;

  return 0;
}

State* StateAlive::nextState(){
    //std::cout << "c A" << celula_->vecinas_[estado(A)] << std::endl;
    //std::cout << "c D " << celula_->vecinas_[estado(D)] << std::endl;
    if ((celula_->vecinas_[A] == 2) || (celula_->vecinas_[A] == 3)){
        return new StateAlive(celula_);
    } else {
        return new StateDead(celula_);
    }
}

estado StateAlive::getState() const{
    return A;
}