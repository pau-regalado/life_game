#ifndef _SEQUENCE_
#define _SEQUENCE_

#include <vector>
#include <array>
#include <list>
#include <iostream>
#include <iomanip>
 
template <class Key>
class Sequence{

  public:
    Sequence(const int Size = 0) {}
    ~Sequence(void){}

    virtual bool Buscarc  (const Key& X) = 0;
    virtual bool Insertarc(const Key&X) = 0;
    virtual bool EstaLleno(void) const = 0;
    virtual void Resize(int size) = 0;
    void print();

    Key at(int i){
      return Self_[i];
    }

    // Mod
    unsigned getSearchTries(void) { return searchTries_; }
    unsigned getInsertTries(void) { return insertTries_; }

    void addInsertTry(void)  { insertTries_++; }
    void addSearchTry(void)  { searchTries_++; }
    void updateMaxCols(int c) { maxCols_ = c; }

    std::vector<Key>& get_self(void);

  protected:
    std::vector<Key> Self_;
    inline static unsigned searchTries_, insertTries_;
    inline static unsigned maxCols_; // For printing
};


template <class Key>
std::vector<Key>& Sequence<Key>::get_self(void) {
  return Self_;
}

template <class Key>
void Sequence<Key>::print() {
  for (int i = 0; i < Self_.size(); ++i) {
    std::cout << std::right << std::setw(10) << Self_[i] << " ";
  }
  if (Self_.size() == 0) {
    for (int j = 0; j < maxCols_; ++j)
      std::cout << std::right << std::setw(10) << "" << " ";
  }
  std::cout << std::left << std::setw(0); // Resetea el formato
}

#endif