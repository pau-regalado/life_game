#ifndef _REJILLA_ 
#define _REJILLA_

#include <iostream>
#include <vector>

class Celula;

class Rejilla {
  private:
    int turno_;
    int nrows_, ncols_;
    std::vector<std::vector<Celula>> rejilla_;

  public:
    Rejilla(int row, int col);
    ~Rejilla();

    void update(void);
    void defecto(void);

    const Celula& getCelula(int, int) const;
    void nextGeneration(void);
    int getTurno(void);

    void printGrid(void);
};

#endif