#include "../include/arbolb.h"

template <class T>
nodo<T>* arbolb<T>::get_raiz(void){
  return raiz_;
}

template <class T>
void arbolb<T>::podar(nodo<T>* nodo){
  if (nodo == nullptr){return;}
  podar(nodo->get_izq());
  podar(nodo->get_der());
  delete nodo;
  nodo = nullptr;
}

template <class T>
bool arbolb<T>::es_vacio(nodo<T>* nodo){
  return nodo == nullptr;
}

template <class T>
bool arbolb<T>::es_hoja(nodo<T>* nodo){
  return !nodo->get_izq() && !nodo->get_der();
}

// Recorridos

template <class T>
void arbolb<T>::rec_preorden(nodo<T>* nodo){
  if (!nodo){return;}
  //proceso nodo->get_data()

  rec_preorden(nodo->get_izq());
  rec_preorden(nodo->get_der());
}

template <class T>
void arbolb<T>::rec_inorden(nodo<T>* nodo){
  if (!nodo){return;}
  rec_preorden(nodo->get_izq());
  //proceso nodo->get_data()
  rec_preorden(nodo->get_der());
}

template <class T>
void arbolb<T>::rec_postorden(nodo<T>* nodo){
  if (!nodo){return;}
  rec_preorden(nodo->get_izq());
  rec_preorden(nodo->get_der());
  //proceso nodo->get_data()
}

template <class T>
void arbolb<T>::rec_niveles(nodo<T>* raiz){
  
    //std::cout << cola.size() << std::endl;

  std::queue<lv_nodo> cola;
  lv_nodo nodo;
  int nivel = 0, nivel_actual = 0;
  lv_nodo lv_raiz(0,raiz);
  cola.push(lv_raiz);
  //std::cout << "nivel " << nivel << ": ";

  while (!cola.empty()){
    nodo = cola.front();
    nivel = nodo.first;

    cola.pop();
    //std::cout << "nivel " << nivel << ": ";
    //std::cout << "[" << nodo.second->get_data() << "]";
    if(nivel > nivel_actual){
      std::cout << std::endl << "nivel " << nivel << ": ";
      nivel_actual = nivel;
      //std::cout << std::endl;

    }
    if (nivel == 0){
        std::cout << "nivel " << nivel_actual << ": ";
    }  
    if(nodo.second != nullptr){
      //procesar nodo.data
      std::cout << "[" << nodo.second->get_data() << "]";

      lv_nodo izq(nivel+1, nodo.second->get_izq());
      lv_nodo der(nivel+1, nodo.second->get_der());

      cola.push(izq);
      cola.push(der);
        
    }else{
       std::cout << "[.]"; // subarbol vacio
    }
  }
  std::cout << std::endl;
}

template <class T>
bool arbolb<T>::busqueda_nivel(nodo<T>* raiz, T X){
  
    //std::cout << cola.size() << std::endl;

  std::queue<lv_nodo> cola;
  lv_nodo nodo;
  int nivel = 0, nivel_actual = 0;
  lv_nodo lv_raiz(0,raiz);
  cola.push(lv_raiz);

  while (!cola.empty()){
    nodo = cola.front();
    nivel_actual = nodo.first;

    cola.pop();

    if(nivel > nivel_actual)
      nivel_actual = nivel;
    
    if(nodo.second != nullptr){
      //procesar nodo.data
      //std::cout << "nivel " << nivel << ": ";
      //std::cout << "[" << nodo.second->get_data() << "]";
      //std::cout << "estoy en el nivel: " << nivel_actual << std::endl;
      if (nodo.second->get_data() == X){
        return true;
      }

      lv_nodo izq(nivel+1, nodo.second->get_izq());
      lv_nodo der(nivel+1, nodo.second->get_der());

      cola.push(izq);
      cola.push(der);
    }
    
      //arbol vacio
  }
  std::cout << std::endl;
  return false;
}

// TAMAÑO Y ALTURAS

template <class T>
const int arbolb<T>::tam(void){
  return tam_rama(raiz_);
}

template <class T>
const int arbolb<T>::tam_rama(nodo<T>* nodo){
  if (nodo == nullptr){return 0;}
  return (1+ tam_rama(nodo->get_izq()) + tam_rama(nodo->get_der()));
}

template <class T>
const int arbolb<T>::alt(void){
  return alt_nodo(raiz_);
}

template <class T>
const int arbolb<T>::alt_nodo(nodo<T>* nodo){
  if (nodo == nullptr){return 0;}
  int alt_i = alt_nodo(nodo->get_izq());
  int alt_d = alt_nodo(nodo->get_der());
  if (alt_d > alt_i){
    return ++alt_d;
  }else{
    return ++alt_i;
  }
}

template <class T>
const bool arbolb<T>::equilibrado(void){
  return equilibrio_rama(raiz_);
}

template <class T>
const bool arbolb<T>::equilibrio_rama(nodo<T>* nodo){
  if(nodo == nullptr){return true;}

  int eq = tam_rama(nodo->get_izq()) - tam_rama(nodo->get_der());

  switch (eq){
    case -1:
      break;
    case 0:
      break;
    case 1: 
      return equilibrio_rama(nodo->get_izq()) && equilibrio_rama(nodo->get_der());
    default: return false;
  }
}

template <class T>
void arbolb<T>::insertar_equi(const T dato){
  if (raiz_ == nullptr){
    raiz_ = new nodo<T> (dato);
  }else{
    insertar_equil_rama(dato,raiz_);
  }
}

template <class T>
void arbolb<T>::insertar_equil_rama(const T dato, nodo<T>* node){
  if (tam_rama(node->get_izq()) <= tam_rama(node->get_der())){
    if(node->get_izq() != nullptr){
      insertar_equil_rama(dato,node->get_izq());
    }else{
      node->set_izq(new nodo<T>(dato));
    }
  }else{
    if(node->get_der() != nullptr){
      insertar_equil_rama(dato,node->get_der());
    }else{
      node->set_der(new nodo<T>(dato));
    }
  }
}