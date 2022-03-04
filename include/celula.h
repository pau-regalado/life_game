#ifndef _CELULA_ 
#define _CELULA_

#include <iostream>

class Rejilla;

enum estado{muerta, viva};

class Celula{
  private:
    int x_, y_;
    int vecinas_vivas_;
    estado estado_;
  public:
    Celula(int x = 0, int y = 0, estado estado = muerta);

    estado getState(void) const;
    int getVivas(void);

    void setState(const estado);
    void setX(const int x);
    void setY(const int y);
    void updateState(void);
    int neighbors(const Rejilla& g);

};

std::ostream& operator<<(std::ostream& os, const Celula& cell);

#endif