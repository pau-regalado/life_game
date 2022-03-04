#ifndef _REJILLA_ 
#define _REJILLA_

#include <iostream>
#include <vector>

#include "celula.h"

class Rejilla {
  private:
    int turno_;
    int nrows_, ncols_;
    std::vector<std::vector<Celula>> rejilla_;

  public:
    Rejilla(int row, int col);
    ~Rejilla();

    void update(void);

    const Celula& getCelula(int, int) const;
    void nextGeneration(void);

    void printGrid(void);
};

#endif