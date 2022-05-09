#ifndef __ARBOLB__
#define __ARBOLB__

#include <iostream>
#include <queue>
#include <utility>

#include "nodo.h"

template <class T>
class arbolb{

  public:
    arbolb(void): raiz_(nullptr){}
    arbolb(nodo<T>* raiz): raiz_(raiz){}
    ~arbolb(){podar(raiz_);}

    // Setters / getters 
    nodo<T>* get_raiz(void);
    void set_raiz(nodo<T>* nodo);

    // Recorridos

    void rec_niveles(nodo<T>* raiz);
    void rec_preorden(nodo<T>* nodo);
    void rec_inorden(nodo<T>* nodo);
    void rec_postorden(nodo<T>* nodo);

    //tipo de dato para recorrido por niveles
    typedef std::pair<int,nodo<T>*> lv_nodo;

    //utiles
    void podar(nodo<T>* nodo);
    bool es_vacio(nodo<T>* nodo);
    bool es_hoja(nodo<T>* nodo);
    void mostrar_arbol(void);
    void mostrar_rama(nodo<T>* nodo);

    // tamaños y alturas

    const int tam(void);
    const int tam_rama(nodo<T>* nodo);

    const int alt(void);
    const int alt_nodo(nodo<T>* nodo);

    const bool equilibrado(void);
    const bool equilibrio_rama(nodo<T>* nodo);

    // insercion

    void insertar_equi(const T dato);
    void insertar_equil_rama(const T dato, nodo<T>* nodo);

    // Busquedas

    bool busqueda_nivel(nodo<T>* nodo, T X);

  private:
    nodo<T>* raiz_;
    int size_;
    unsigned niveles_;
};



#endif