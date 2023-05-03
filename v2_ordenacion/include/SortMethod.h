#ifndef __SORTMETHOD__
#define __SORTMETHOD__

#include <iostream>
#include <vector>
#include <climits>
#include <chrono>

#include "commons.h"

template<class Key>
class SortMethod {
  protected:
    unsigned size_;
    std::vector<Key>* seq_;
    int timer_;

  public:
    SortMethod(std::vector<Key>* v, unsigned size): seq_(v), size_(size){}
    virtual void Sort() = 0;
    
    std::chrono::microseconds sort_time() {
      auto start = std::chrono::high_resolution_clock::now();
      Sort();
      auto stop  = std::chrono::high_resolution_clock::now();
      return std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    }

    // void mostrar_v(std::vector<Key>* v);
    // std::ostream& operator<<(std::ostream& os/*std::vector<Key>* v*/);
    // void swap(std::vector<Key>* vector, int x, int y);
};

#endif