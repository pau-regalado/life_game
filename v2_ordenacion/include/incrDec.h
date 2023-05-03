#ifndef _INCR_DEC_
#define _INCR_DEC_

#include "SortMethod.h"

template <class Key>
class IncrDecMethod: public SortMethod<Key>{
  private:
    float alpha_;
  public:
    IncrDecMethod(std::vector<Key>* v, float alpha, unsigned size): SortMethod<Key>{ v, size}, alpha_(alpha) {}
    void Sort() {
      incr_dec(this->seq_, alpha_, this->size_);
    }
    void sort(std::vector<Key>* vector, int delta, int size){
      Key x; 
      int j;
      //std::cout << " delta = " << delta << std::endl;
      for(int i = delta; i < size; i++){
        x = vector->at(i);
        j = i;
        while ((j >= delta) && (x < vector->at(j - delta))){  
          vector->at(j) = vector->at(j - delta);
          j = j - delta;
        }
        vector->at(j) = x;
        //mostrar_v(vector);
      }
    }

    void incr_dec(std::vector<Key>* vector, float alpha, int size){
      int delta = size;
      while(delta > 1){
        delta = int(delta * alpha);
        if (delta < 1) {
          delta = 1;
        }
        sort(vector, delta, size);
      }
    }
};

#endif