#ifndef _STATE_ 
#define _STATE_

#include <iostream>
#include "enum.h"

class Rejilla;
class Celula;
class Grid;

// Clase abstracta | todos los metodos son virtuales puros
class State {
  public:
    virtual int neighbors(const Grid&, int i, int j ) = 0;
    virtual State* nextState() = 0;
    virtual estado getState() const = 0;
};

class StateDead: public State {
  private:
    // Para enlazar con la celula y poder
    // acceder a sus datos
    Celula* celula_;  
    int nVivas;
  public:
    StateDead(Celula* c):celula_(c){}
    ~StateDead(){
      celula_ = nullptr;
    }
    virtual int neighbors(const Grid&, int i, int j );
    virtual State* nextState();
    virtual estado getState() const;
};

class StateAlive: public State {
  private:
    Celula* celula_;
  public:
    StateAlive(Celula* c):celula_(c){}
    ~StateAlive(){
      //delete celula_;
    }
    virtual int neighbors(const Grid&, int i, int j );
    virtual State* nextState();
    virtual estado getState() const;
};

#endif