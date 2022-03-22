#ifndef _CELULA_ 
#define _CELULA_

#include <vector>
#include <iostream>
#include "enum.h"

class Rejilla;
class State;
class Grid;

class Celula{
  private:
    //int vecinas_vivas_;
    int x_, y_;
    State* estado_; // Apunta a un tipo de estado en concreto para  polimorfismo

  public:
    std::vector<int> vecinas_;

    Celula(int x = 0, int y = 0, State* estado = nullptr);
    ~Celula(void);

    State const* getState(void) const;
    int getVivas(void);
    std::vector<int>& getVecinas(void);

    void clearVecinas(void);

    void setState(State *estado);
    void setX(const int x);
    void setY(const int y);

    int getX(void) const;
    int getY(void);

    void updateState(void);
    void neighbors(const Grid& g);

};

std::ostream& operator<<(std::ostream& os, const Celula& cell);

#endif