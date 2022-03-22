#ifndef _REJILLA_ 
#define _REJILLA_

#include <iostream>
#include <vector>
#include <string>

const int defSize = 10;

class Celula;

class Grid{
  protected:
    int turno_;
    int nrows_, ncols_;
    Celula** rejilla_;

  public:
    // Grid(int row = defSize, int col = defSize);
    virtual ~Grid() = 0;

    // Initialitation
    void defecto(void);
    void insert(void);

    virtual Celula& getCelula(int, int) = 0; // if i o j - || 0 then coger su propia x y
    virtual const Celula& getCelula(int, int) const = 0;
    virtual std::string getName(void) = 0;
    int getRow(void){ return nrows_;}
    int getCol(void){ return ncols_;}

    virtual void print() = 0;
    friend std::ostream& operator<<(std::ostream& os, Grid &g);

    void nextGeneration(void);
};

class GridWithPeriodicBorder: public Grid{
  public:
    GridWithPeriodicBorder(int row, int col);
    ~GridWithPeriodicBorder();

    Celula& getCelula(int, int);
    const Celula& getCelula(int, int) const;
    std::string getName(void){return "Periodic";}

    virtual void print();
};

class GridWithReflectiveBorder: public Grid{
  public:
    GridWithReflectiveBorder(int row, int col);
    ~GridWithReflectiveBorder();

    Celula& getCell(int, int) {}
    const Celula& getCell(int, int) const{}
};

class GridWithOpenBorder: public Grid{
  public:
    GridWithOpenBorder(int row, int col);
    ~GridWithOpenBorder();

    Celula& getCelula(int, int);
    const Celula& getCelula(int, int) const;
    std::string getName(void){return "Open";}

    //std::ostream& operator<<(std::ostream& os);
    virtual void print();
};


#endif