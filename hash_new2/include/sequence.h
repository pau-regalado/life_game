#ifndef _SEQUENCE_
#define _SEQUENCE_

#include <vector>
#include <array>
#include <list>
#include <iostream>
 
template <class Key>
class Sequence{

  public:
    Sequence(const int Size = 0) {}
    ~Sequence(void){}

    virtual bool Buscarc  (const Key& X) = 0;
    virtual bool Insertarc(const Key&X) = 0;
    virtual bool EstaLleno(void) const = 0;
    virtual void Resize(int size) = 0;
    virtual void print() = 0;

    Key at(int i){
      return Self_[i];
    }

    // Mod
    unsigned getInsertElements(void) { return insertElements_; }
    unsigned getSearchElements(void) { return searchElements_; }

    void addInsertElements(void) { insertElements_++; }
    void addSearchElements(void) { searchElements_++; }

    std::vector<Key>& get_self(void);

  protected:
    std::vector<Key> Self_;
    inline static unsigned insertElements_, searchElements_;
};


template <class Key>
std::vector<Key>& Sequence<Key>::get_self(void) {
  return Self_;
}

#endif