#ifndef __PALABRA__
#define __PALABRA__

#include <iostream>

template <class T>
class palabra{
  public:
    palabra(void);
    nodo(T data, T clave, nodo<T>* izq = nullptr, nodo<T>* der = nullptr);
    ~nodo(void);
    // getter / setters 

    nodo<T>* get_izq(void);
    nodo<T>* get_der(void);
    T        get_data(void);
    T        get_clave(void);

    void set_izq(nodo<T>* izq);
    void set_der(nodo<T>* der);    
    void set_data(T data);
    void set_clave(T clave);

    nodo<T>& operator= (nodo<T>& node);

  private:
    T data_;
    T clave_;
    nodo<T>* h_der_;
    nodo<T>* h_izq_;
};

#endif