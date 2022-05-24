#ifndef __AVL__
#define __AVL__

#include <iostream>
#include <queue>
#include <utility>

#include "ABB.h"

template <class Key>
class AVL: public ABB<Key>{

  public:
    AVL(void): ABB<Key>(nullptr), traceMode_(false){}
    AVL(NodoAVL<Key>* raiz): AB<Key>(raiz), traceMode_(false){}
    // ~AVL(){}
    void setTraceMode(bool mode);

    bool insertar(const Key dato);
    void insertarBalanceado(NodoAVL<Key>* &nodo, NodoAVL<Key>* &nuevo, bool& crece);
    void insertarReBalanceaIzquierda(NodoAVL<Key>* &nodo, bool& crece);
    void insertarReBalanceaDerecha  (NodoAVL<Key>* &nodo, bool& crece);

    bool equilibrado(void);
    bool equilibrioRama(NodoAVL<Key>* nodo);

    // Busquedas
    bool buscar(const Key& X);
    bool buscarRama(NodoAVL<Key>* nodo, const Key& X);

    void rotacionII(NodoAVL<Key>* &nodo);
    void rotacionID(NodoAVL<Key>* &nodo);
    void rotacionDI(NodoAVL<Key>* &nodo);
    void rotacionDD(NodoAVL<Key>* &nodo);

    // Eliminacion no implementada en esta clase
    void sustituye(NodoAVL<Key>* &eliminado, NodoAVL<Key>* &sustituto, bool& decrece);
    bool eliminar(const Key& X);
    bool eliminarRama(NodoAVL<Key>* &nodo, const Key& X, bool& decrece);
    void eliminarReBalanceaIzquierda(NodoAVL<Key>* &nodo, bool& decrece);
    void eliminarReBalanceaDerecha  (NodoAVL<Key>* &nodo, bool& decrece);
  
  private:
    bool traceMode_;
};

template <class Key>
void AVL<Key>::setTraceMode(bool mode) {
  traceMode_ = mode;
}

template <class Key>
void AVL<Key>::insertarReBalanceaIzquierda(NodoAVL<Key>* &nodo, bool& crece) {
  switch (nodo->getBal()) {
    case -1:
      std::cout << "Entro en case -1 en ins bal izq" << std::endl;
      nodo->getBal() = 0;
      crece = false;
      break;
    case 0:
      std::cout << "Entro en case 0 en ins bal izq" << std::endl;
      nodo->getBal() = 1;
      break;
    case 1:
      std::cout << "Entro en case 1 en ins bal izq" << std::endl;
      NodoAVL<Key>* nodo1 = nodo->getIzq();
      if (nodo1->getBal() == 1) {
        rotacionII(nodo);
      } else {
        rotacionID(nodo);
      }
      crece = false;
      break;
  }
  std::cout << "Salgo de ins bal izq" << std::endl;
}

template <class Key>
void AVL<Key>::insertarReBalanceaDerecha(NodoAVL<Key>* &nodo, bool& crece) {
  switch (nodo->getBal()) {
    case 1:
      std::cout << "Entro en case 1 en ins bal der" << std::endl;
      nodo->getBal() = 0;
      crece = false;
      break;
    case 0:
      std::cout << "Entro en case 0 en ins bal der" << std::endl;
      nodo->getBal() = -1;
      break;
    case -1:
      std::cout << "Entro en case -1 en ins bal der" << std::endl;
      NodoAVL<Key>* nodo1 = nodo->getDer();
      if (nodo1->getBal() == -1) {
        rotacionDD(nodo);
      } else {
        rotacionDI(nodo);
      }
      crece = false;
      break;
  }
  std::cout << "Salgo de ins bal der" << std::endl;
}

template <class Key>
bool AVL<Key>::insertar(const Key dato) {
  if (buscar(dato))
   return false;
  else {
    NodoAVL<Key>* nuevo = new NodoAVL<Key>(dato, dato);
    nuevo->getBal() = 0;
    bool crece = false;
    insertarBalanceado(this->getRaiz(), nuevo, crece);
    return true;
  }
}

template <class Key>
void AVL<Key>::insertarBalanceado(NodoAVL<Key>* &nodo, NodoAVL<Key>* &nuevo, bool& crece) {
  if (nodo == nullptr) {
    nodo = nuevo;
    crece = true;
  } else if (nuevo->getData() < nodo->getData()) {
    insertarBalanceado(nodo->getIzq() , nuevo, crece);
    if (crece)
      insertarReBalanceaIzquierda(nodo, crece);
  } else {
    insertarBalanceado(nodo->getDer() , nuevo, crece);
    if (crece)
      insertarReBalanceaDerecha(nodo, crece);
  }
}


template <class Key>
bool AVL<Key>::buscar(const Key& X) {
  return buscarRama(this->getRaiz(), X);
}

template <class Key>
bool AVL<Key>::buscarRama(NodoAVL<Key>* nodo, const Key& X) {
  if (!nodo) {
    return false;
  }
  if (X == nodo->getData()) {
    return true;
  }
  if (X < nodo->getData())
    return buscarRama(nodo->getIzq(), X);
  return buscarRama(nodo->getDer(), X);
}

template <class Key>
void AVL<Key>::sustituye(NodoAVL<Key>* &eliminado, NodoAVL<Key>* &sustituto, bool& decrece) {
  if (sustituto->getDer()) {
    sustituye(eliminado, sustituto->getDer(), decrece);
    if (decrece)
      eliminarReBalanceaDerecha(sustituto, decrece);
  } else {
    eliminado->setClave(sustituto->getClave());
    eliminado->setData(sustituto->getData());
    eliminado = sustituto;
    sustituto = sustituto->getIzq();
    decrece = true;
  }
}

template <class Key>
bool  AVL<Key>::eliminar(const Key& X) {
  bool decrece = false;
  return eliminarRama(this->getRaiz(), X , decrece);
}

template <class Key>
bool  AVL<Key>::eliminarRama(NodoAVL<Key>* &nodo, const Key& clave, bool& decrece) {
  if (!nodo) {
    return false;
  } else {  
    if (clave < nodo->getData()) {
      eliminarRama(nodo->getIzq(), clave, decrece);
      if (decrece) {
        eliminarReBalanceaIzquierda(nodo, decrece);
      }
    } else if (clave > nodo->getData()) {
      eliminarRama(nodo->getDer(), clave, decrece);
      if (decrece) {
        eliminarReBalanceaDerecha(nodo, decrece);
      }
    } else {
      NodoAVL<Key>* eliminado = nodo;
      if (!nodo->getIzq()) {
        nodo = nodo->getDer();
        decrece = true;
      } else if (!nodo->getDer()) {
        nodo = nodo->getIzq();
        decrece = true;
      } else {
        sustituye(eliminado, nodo->getIzq() , decrece);
        if (decrece) {
          eliminarReBalanceaIzquierda(nodo, decrece);
        }
      }
      delete eliminado;
    }
    return true;
  }
}

template <class Key>
void AVL<Key>::eliminarReBalanceaIzquierda(NodoAVL<Key>* &nodo, bool& decrece) {
  switch (nodo->getBal()) {
    case -1:{
      NodoAVL<Key> *nodo1 = nodo->getDer();
      if (nodo1->getBal() > 0) {
        rotacionDI(nodo);
      } else {
        if (nodo1->getBal() == 0) {
          decrece = false;
        }
        rotacionDD(nodo);
      }
      break;
    }
    case 0:
      nodo->getBal() = -1;
      decrece = false;
      break;
    case 1: {
      nodo->getBal() = 0;
    }
  }
}

template <class Key>
void AVL<Key>::eliminarReBalanceaDerecha(NodoAVL<Key>* &nodo, bool& decrece) {
  switch (nodo->getBal()) {
    case 1:{
      NodoAVL<Key> *nodo1 = nodo->getIzq();
      if (nodo1->getBal() < 0) {
        rotacionID(nodo);
      } else {
        if (nodo1->getBal() == 0) {
          decrece = false;
        }
        rotacionII(nodo);
      }
      break;
    }
    case 0:
      nodo->getBal() = 1;
      decrece = false;
      break;
    case -1: {
      nodo->getBal() = 0;
    }
  }
}

template <class Key>
void AVL<Key>::rotacionII(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->getIzq();
  nodo->getIzq() = nodo1->getDer();
  nodo1->getDer() = nodo;

  if (nodo1->getBal() == 1) {
    nodo->getBal() = 0;
    nodo1->getBal() = 0;
  } else {
    nodo->getBal() = 1;
    nodo1->getBal() = -1;
  }
  nodo = nodo1;
  std::cout << *this << std::endl;
}

template <class Key>
void AVL<Key>::rotacionDD(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->getDer();
  nodo->getDer() = nodo1->getIzq();
  nodo1->getIzq() = nodo;

  if (nodo1->getBal() == -1) {
    nodo->getBal() = 0;
    nodo1->getBal() = 0;
  } else {
    nodo->getBal() = -1;
    nodo1->getBal() = 1;
  }
  nodo = nodo1; 
  std::cout << *this << std::endl;
}

template <class Key>
void AVL<Key>::rotacionID(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->getIzq();
  NodoAVL<Key>* nodo2 = nodo1->getDer();
  nodo->getIzq() = nodo2->getDer();
  nodo2->getDer() = nodo;
  nodo1->getDer() = nodo2->getIzq();
  nodo2->getIzq() = nodo1;

  if (nodo2->getBal() == -1) {
    nodo1->getBal() = 1;
  } else {
    nodo1->getBal() = 0;
  }
  if (nodo2->getBal() == 1) {
    nodo->getBal() = -1;
  } else {
    nodo->getBal() = 0;
  }
  nodo2->getBal() = 0;
  nodo = nodo2;
    std::cout << *this << std::endl;
}

template <class Key>
void AVL<Key>::rotacionDI(NodoAVL<Key>* &nodo) {
  NodoAVL<Key>* nodo1 = nodo->getDer();
  NodoAVL<Key>* nodo2 = nodo1->getIzq();
  nodo->getDer() = nodo2->getIzq();
  nodo2->getIzq() = nodo;
  nodo1->getIzq() = nodo2->getDer();
  nodo2->getDer() = nodo1;

  if (nodo2->getBal() == 1) {
    nodo1->getBal() = -1;
  } else {
    nodo1->getBal() = 0;
  }
  if (nodo2->getBal() == -1) {
    nodo->getBal() = 1;
  } else {
    nodo->getBal() = 0;
  }
  nodo2->getBal() = 0;
  nodo = nodo2;
    std::cout << *this << std::endl;
}

#endif