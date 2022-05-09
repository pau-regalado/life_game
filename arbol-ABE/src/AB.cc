#include "../include/AB.h"

template <class Key>
NodoB<Key>* AB<Key>::getRaiz(void){
  return raiz_;
}

template <class Key>
void AB<Key>::podar(NodoB<Key>* nodo){
  if (nodo == nullptr){return;}
  podar(nodo->getIzq());
  podar(nodo->getDer());
  delete nodo;
  nodo = nullptr;
}

template <class Key>
bool AB<Key>::es_vacio(NodoB<Key>* nodo){
  return nodo == nullptr;
}

template <class Key>
bool AB<Key>::es_hoja(NodoB<Key>* nodo){
  return !nodo->getIzq() && !nodo->getDer();
}

template <class Key>
void AB<Key>::inorden(NodoB<Key>* nodo) const{
  if (!nodo){return;}
  inorden(nodo->getIzq());
  //proceso NodoB->get_data()
  inorden(nodo->getDer());
}


template <class Key>
void AB<Key>::recorridoNiveles(NodoB<Key>* raiz){
  
  // tipo de dato para recorrido por niveles
  typedef std::pair<int,NodoB<Key>*> leveledNodoB;
    //std::cout << cola.size() << std::endl;

  std::queue<leveledNodoB> cola;
  leveledNodoB lvAux;
  int nivel = 0, nivelActual = 0;
  cola.push(lvRaiz(0, raiz_));
  //std::cout << "nivel " << nivel << ": ";

  while (!cola.empty()){
    lvAux = cola.pop();

    nivel = lvAux.first;

    //std::cout << "nivel " << nivel << ": ";
    //std::cout << "[" << NodoB.second->get_data() << "]";
    if(nivel > nivelActual){
      std::cout << std::endl << "nivel " << nivel << ": ";
      nivelActual = nivel;
      //std::cout << std::endl;

    }
    if (nivel == 0){
        std::cout << "nivel " << nivelActual << ": ";
    }  
    if(lvAux.second != nullptr){

      std::cout << "[" << lvAux.second->getData() << "]";

      cola.push(nivel + 1, lvAux.second->getIzq());
      cola.push(nivel + 1, lvAux.second->getDer());
        
    }else{
       std::cout << "[.]"; // subarbol vacio
    }
  }
  std::cout << std::endl;
}

template <class Key>
const int AB<Key>::tam(void){
  return tamRama(raiz_);
}

template <class Key>
const int AB<Key>::tamRama(NodoB<Key>* nodo){
  if (nodo == nullptr){return 0;}
    return (1 + tamRama(nodo->getIzq()) + tamRama(nodo->getDer()));
}

template <class Key>
const int AB<Key>::alt(void){
  return altNodo(raiz_);
}

template <class Key>
const int AB<Key>::altNodo(NodoB<Key>* nodo){
  if (nodo == nullptr){return 0;}
  int alt_i = altNodo(nodo->getIzq());
  int alt_d = altNodo(nodo->getDer());
  // Retornamos el mas alto mas 1 del nivel actual
  if (alt_d > alt_i){
    return ++alt_d;
  }else{
    return ++alt_i;
  }
}