#ifndef _STATE_ 
#define _STATE_

#include <iostream>

class Rejilla;
class Celula;

class State {
  public:
    virtual int neighbors(const Rejilla&, int i, int j )= 0;
    virtual State* nextState() = 0;
    virtual char getState() const = 0;
};

class StateDead: public State {
  private:
    Celula* celula_;
    int nAdultas;
  public:
    StateDead(Celula* c):celula_(c){}
    ~StateDead(){
      //delete celula_;
    }
    virtual int neighbors(const Rejilla&, int i, int j );
    virtual State* nextState();
    virtual char getState() const;
};

class StateEgg: public State {
  private:
    Celula* celula_;
    int nLarvas, nHuevos;
  public:
    StateEgg(Celula* c):celula_(c){}
    ~StateEgg(){
      //delete celula_;
    }
    virtual int neighbors(const Rejilla&, int i, int j );
    virtual State* nextState();
    virtual char getState() const;
};

class StateLarva: public State {
  private:
    Celula* celula_;
  public:
    StateLarva(Celula* c):celula_(c){}
    ~StateLarva(){
      //delete celula_;
    }
    virtual int neighbors(const Rejilla&, int i, int j );
    virtual State* nextState();
    virtual char getState() const;
};

class StatePupa: public State {
  private:
    Celula* celula_;
  public:
    StatePupa(Celula* c):celula_(c){}
    ~StatePupa(){
      //delete celula_;
    }
    virtual int neighbors(const Rejilla&, int i, int j );
    virtual State* nextState();
    virtual char getState() const;
};

class StateAdult: public State {
  private:
    Celula* celula_;
  public:
    StateAdult(Celula* c):celula_(c){}
    ~StateAdult(){
      //delete celula_;
    }
    virtual int neighbors(const Rejilla&, int i, int j );
    virtual State* nextState();
    virtual char getState() const;
};

#endif