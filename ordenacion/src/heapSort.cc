#include "../include/heapSort.h"

template <class Clave>
void baja(std::vector<Clave>* vector, int index, int size){
  char step;

  while(2*index <= size){
    //std::cout << "index: " << index << std::endl;
    int h1 = 2*index;
    int h2 = h1+1;
    int h;
    //std::cout << "antes de los ifs: index = " << index << " h1 = " << h1 << " h2 = " << h2 << " h = " << h << std::endl;
    //std::cin >> step;
    if (h1 == size){
      h = h1;
    }else if(vector->at(h1-1) > vector->at(h2-1)){
      h = h1;
    }else{ 
      h = h2;
    }
    //std::cout << "despues de los ifs: index = " << index << " h1 = " << h1 << " h2 = " << h2 << " h = " << h << std::endl;
    //std::cin >> step;
    if(vector->at(h-1) <= vector->at(index-1)){
    break;
    }else{
      //std::cout << "entro al if" << std::endl;
      swap(vector,index-1,h-1);
      //std::cout << "entro al if" << std::endl;
      index = h;
    }
    //std::cout << "despues todo: index = " << index << std::endl;
    //std::cin >> step;    
    mostrar_v(vector);
  }
}

template <class Clave>
void heapsort(std::vector<Clave>* vector, int size){
  char step;
  for (int i = size/2; i > 0; i--){
    //std::cout << "entro al 1 for. i = " << i << " size = " << size << std::endl;
    //std::cin >> step;    
    baja(vector,i,size-1);
  }

  for (int i = size; i > 1; i--){
    //std::cout << "########entro al 2 for. i = " << i << " size = " << size << std::endl;
    //std::cin >> step; 
    swap(vector,1-1,i-1);
    baja(vector,1,i-1);
  }
}