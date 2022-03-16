#ifndef _CELULA_ 
#define _CELULA_

#include <vector>
//#include "state.h"

#include <iostream>

class Rejilla;
class State;

enum estado{D, E, L, P, A};

class Celula{
  private:
    int x_, y_;
    int vecinas_vivas_;
    State* estado_;

  public:
    std::vector<int> vecinas_;

    Celula(int x = 0, int y = 0, State* estado = nullptr);
    ~Celula(void);

    State* getState(void) const;
    int getVivas(void);
    std::vector<int>& getVecinas(void);

    void clearVecinas(void);

    void setState(State *estado);
    void setX(const int x);
    void setY(const int y);

    int getX(void);
    int getY(void);

    void updateState(void);
    void neighbors(const Rejilla& g);

};

std::ostream& operator<<(std::ostream& os, const Celula& cell);

#endif