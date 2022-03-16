#include "../include/state.h"
#include "../include/rejilla.h"
#include "../include/celula.h"

// StateDead -------------------------------------------------

int StateDead::neighbors(const Rejilla& grid, int i, int j ) {
  /*Este va a mirar todos sus vecinos que sean huevo y
  va a devolver est numero para luego ennesct estate comprobar
  que sea mayor que 2*/
  nAdultas = 0;

  celula_->clearVecinas(); // Reseteamos las vecinas

  if(grid.getCelula(i - 1, j - 1).getState()->getState() == 'E'){nAdultas++;}
  if(grid.getCelula(i - 1, j    ).getState()->getState() == 'E'){nAdultas++;}
  if(grid.getCelula(i - 1, j + 1).getState()->getState() == 'E'){nAdultas++;}
  if(grid.getCelula(i    , j - 1).getState()->getState() == 'E'){nAdultas++;}
  if(grid.getCelula(i    , j + 1).getState()->getState() == 'E'){nAdultas++;}
  if(grid.getCelula(i + 1, j - 1).getState()->getState() == 'E'){nAdultas++;}
  if(grid.getCelula(i + 1, j    ).getState()->getState() == 'E'){nAdultas++;}
  if(grid.getCelula(i + 1, j + 1).getState()->getState() == 'E'){nAdultas++;}
  return nAdultas;
}

State* StateDead::nextState(){
    if (nAdultas < 2){
        return new StateDead(celula_);
    } else {
        return new StateLarva(celula_);
    }
}

char StateDead::getState() const{
    return 'D';
}

// StateEgg -------------------------------------------------

int StateEgg::neighbors(const Rejilla& grid, int i, int j ) {
    /*Calcula el numero de larvas y el de huevos, retorna la resta
    para luego comprobar si es prositivo => muerta: larva*/

  celula_->clearVecinas(); // Reseteamos las vecinas

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

State* StateEgg::nextState(){
    if (celula_->vecinas_['L'] > celula_->vecinas_['H']){//larva > huevo){
        return new StateDead(celula_);
    } else {
        return new StateLarva(celula_);
    }
}

char StateEgg::getState() const{
    return 'E';
}

// StateLarva -------------------------------------------------

int StateLarva::neighbors(const Rejilla& grid, int i, int j ) {
    /*Calcula el numero de larvas y la suma de los estados 
    huevo pupa y adulto, si resta positiva => muerta: pupa*/

  celula_->clearVecinas(); // Reseteamos las vecinas

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

State* StateLarva::nextState(){
    if (celula_->vecinas_['L'] > 
       (celula_->vecinas_['E'] + celula_->vecinas_['P'] + celula_->vecinas_['A'])){
        return new StateDead(celula_);
    } else {
        return new StatePupa(celula_);
    }
}

char StateLarva::getState() const{
    return 'L';
}

// StatePupa -------------------------------------------------

int StatePupa::neighbors(const Rejilla& grid, int i, int j ) {
    /* larva > resto? muerta: adulta
    n larva - (n resto - n muerta) */
  
  celula_->clearVecinas(); // Reseteamos las vecinas

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

State* StatePupa::nextState(){
    if ((celula_->vecinas_['L'] > 
                                  (celula_->vecinas_['D'] +
                                   celula_->vecinas_['E'] + 
                                   celula_->vecinas_['P'] + 
                                   celula_->vecinas_['A']))){//larva > huevo){
        return new StateDead(celula_);
    } else {
        return new StateAdult(celula_);
    }
}

char StatePupa::getState() const{
    return 'P';
}

// State Adult -------------------------------------------------

int StateAdult::neighbors(const Rejilla& grid, int i, int j ) {
  
    /* nAdultas >= 1 */
  
  celula_->clearVecinas(); // Reseteamos las vecinas

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

State* StateAdult::nextState(){
    if (celula_->vecinas_['A'] >= 1){//larva > huevo){
        return new StateEgg(celula_);
    } else {
        return new StateDead(celula_);
    }
}

char StateAdult::getState() const{
    return 'A';
}