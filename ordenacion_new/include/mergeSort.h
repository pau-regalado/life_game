#ifndef _MERGESORT_
#define _MERGESORT_

#include "commons.h" 

template <class Clave>
void mezcla(std::vector<Clave>* vector, int ini, int cent, int fin){
  int i = ini, j = cent+1;
  int k = ini;
  //std::cout << "entro mezcla con:"<< std::endl;
  //std::cout << "ini = " << ini << " cent = " << cent << " fin = " << fin << std::endl;
  std::vector<Clave> aux(fin+1);
  //aux.resize(fin+1);
  while((i <= cent) && (j <= fin)){
    //std::cout << "entro al while"<< std::endl;
    if (vector->at(i) < vector->at(j)){
      //std::cout << "entro al if"<< std::endl;
      aux.at(k) = vector->at(i);
      //std::cout << "asigne"<< std::endl;
      i++;
    }else{
      //std::cout << "entro al else"<< std::endl;
      aux.at(k) = vector->at(j);
      //std::cout << "asigne"<< std::endl;
      j++;
    }
    k++;
  } 
  //std::cout << "salgo del prin k = " << k << " j = " << j << " i = " << i <<std::endl;

  if(i > cent){
    while (j <= fin){
      //std::cout << "entro al 2 while con k = " << k << " j = " << j << std::endl;
      aux.at(k) = vector->at(j);
      j++;
      k++;
    }
  }else{
    while (i <= cent){
      //std::cout << "entro al 3 while con k = " << k << " j = " << j << std::endl;
      aux.at(k) = vector->at(i);
      i++;
      k++;        
    }
  }
  //std::cout << "entro al for l" << std::endl;
  for(int l = ini; l <= fin; l++){
    vector->at(l) = aux.at(l);
  }
  //std::cout << "sali del for l" << std::endl;
  mostrar_v(vector);
}


template <class Clave>
void mergesort(std::vector<Clave>* vector, int inicio, int fin){
  if (inicio < fin){
    int cent = (inicio + fin)/2;
    //std::cout << "cent = " << cent << std::endl;
    mergesort(vector,inicio,cent);
    mergesort(vector,cent+1,fin);
    mezcla(vector,inicio,cent,fin);
  }
}

#endif