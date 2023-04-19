#ifndef __SORTMETHOD__
#define __SORTMETHOD__

#include <iostream>
#include <vector>
#include <climits>

#include "commons.h"

template<class Key>
class SortMethod {
  protected:
    unsigned size_;
    std::vector<Key>* seq_;
  public:
    SortMethod(std::vector<Key>* v, unsigned size): seq_(v), size_(size){}
    virtual void Sort() = 0;
    // void mostrar_v(std::vector<Key>* v);
    // std::ostream& operator<<(std::ostream& os/*std::vector<Key>* v*/);
    // void swap(std::vector<Key>* vector, int x, int y);
};

#endif