#ifndef __AB__
#define __AB__

#include <iostream>
#include <queue>
#include <utility>

#include "NodoB.h"

// tipo de dato para recorrido por niveles
// template <typename Key>
// typedef std::pair<int,NodoB<Key>*> lv_NodoB;

// Clase que representa un arbol binario
template <class Key>
class AB{

  public:
    AB(void): raiz_(nullptr){}
    AB(NodoB<Key>* raiz): raiz_(raiz){}
    ~AB(){podar(raiz_);}

    // Setters / getters 
    NodoB<Key>*& getRaiz(void);
    void setRaiz(NodoB<Key>* nodo);

    // Recorridos
    void inorden(NodoB<Key>* nodo) const;
    void recorridoNiveles(void);

    //utiles
    void podar(NodoB<Key>* nodo);
    bool es_vacio(NodoB<Key>* nodo);
    bool es_hoja(NodoB<Key>* nodo);
    // void mostrar_arbol(void);
    // void mostrarRama(NodoB<Key>* nodo);

    // tamaños y alturas

    const int tam(void);
    const int tamRama(NodoB<Key>* nodo);

    const int alt(void);
    const int altNodo(NodoB<Key>* nodo);

    // insercion
    virtual bool insertar(const Key dato) = 0; 

    // Busquedas
    virtual bool buscar(const Key& X) = 0;

    // Eliminacion
    virtual bool eliminar(const Key& X) = 0;

  protected:
    NodoB<Key>* raiz_;
    int size_;
    unsigned niveles_;
};

template <class Key>
NodoB<Key>*& AB<Key>::getRaiz(void){
  return raiz_;
}

template <class Key>
void AB<Key>::setRaiz(NodoB<Key>* raiz){
  raiz_ = raiz;
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
void AB<Key>::recorridoNiveles(void){
  std::queue<std::pair<NodoB<Key>*,int>> Q;
  NodoB<Key> *nodo;
  int nivel, Nivel_actual = 0;
  Q.push(std::make_pair(raiz_, 0));

  std::cout << "Nivel 0: ";
  //Recorremos la cola hasta que este vacia
  while (!Q.empty()) {
    //Guardamos el primer valor de la cola
    std::pair<NodoB<Key>*,int> p;
    p = Q.front();
    nodo = p.first;
    nivel = p.second;
    //Quitamos la pareja(nodo,nivel) de la Cola
    Q.pop();
    if(nivel > Nivel_actual) {
      Nivel_actual = nivel;
      std::cout << "\nNivel " << Nivel_actual << ": ";
    }
    //Mostramos el valor del nodo
    if (nodo != NULL) {
      std::cout << "[" << nodo->getData() << "]";
      Q.push(std::make_pair(nodo->getIzq(),nivel + 1));
      Q.push(std::make_pair(nodo->getDer(),nivel + 1));
    } else {
      if (Nivel_actual == 0) {
        std::cout << "[.]";
      }
    }
  }
  std::cout << "\n";
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

template <class Key>
std::ostream& operator<< (std::ostream& os, AB<Key>& a) {
  std::queue<std::pair<NodoB<Key>*,int>> Q;
  NodoB<Key> *nodo;
  int nivel, Nivel_actual = 0;
  Q.push(std::make_pair(a.getRaiz(), 0));

  os << "Nivel 0: ";
  //Recorremos la cola hasta que este vacia
  while (!Q.empty()) {
    //Guardamos el primer valor de la cola
    std::pair<NodoB<Key>*,int> p;
    p = Q.front();
    nodo = p.first;
    nivel = p.second;
    //Quitamos la pareja(nodo,nivel) de la Cola
    Q.pop();
    if(nivel > Nivel_actual) {
      Nivel_actual = nivel;
      os << "\nNivel " << Nivel_actual << ": ";
    }
    //Mostramos el valor del nodo
    if (nodo != NULL) {
      os << "[" << nodo->getData() << "]";
      Q.push(std::make_pair(nodo->getIzq(),nivel + 1));
      Q.push(std::make_pair(nodo->getDer(),nivel + 1));
    } else {
      // if (Nivel_actual == 0) {
        os << "[.]";
      // }
    }
  }
  os << "\n";
  return os;
}

#endif