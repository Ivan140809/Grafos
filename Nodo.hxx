#ifndef NODO_HXX
#define NODO_HXX

template <class T>
Arista<T>::Arista(Nodo<T>* d, int p) {
destino = d;
peso = p;
}

template <class T>
Nodo<T>::Nodo(T valor) {
 dato = valor;
 visitado = false;
 nivel = -1;
}

template <class T>
T Nodo<T>::getDato() {
 return dato;
}

template <class T>
void Nodo<T>::setDato(T valor) {
 dato = valor;
}

template <class T>
bool Nodo<T>::getVisitado() {
 return visitado;
}

template <class T>
void Nodo<T>::setVisitado(bool v) {
 visitado = v;
}

template <class T>
int Nodo<T>::getNivel() {
 return nivel;
}

template <class T>
void Nodo<T>::setNivel(int n) {
 nivel = n;
}

template <class T>
list<Arista<T> >& Nodo<T>::getAdyacentes() {
 return adyacentes;
}

template <class T>
void Nodo<T>::agregarAdyacente(Nodo<T>* destino, int peso) {
if (destino == NULL) {
      return;
}
if (!esAdyacente(destino)) {
  Arista<T> nuevaArista(destino, peso);
  adyacentes.push_back(nuevaArista);
     }
 }

template <class T>
void Nodo<T>::eliminarAdyacente(Nodo<T>* destino) {
 typename list<Arista<T>>::iterator it = adyacentes.begin();
 while (it != adyacentes.end()) {
    if (it->destino == destino) {
      it = adyacentes.erase(it);
     } else {
       ++it;
     }
  }
}

template <class T>
bool Nodo<T>::esAdyacente(Nodo<T>* destino) {
  typename list<Arista<T>>::iterator it = adyacentes.begin();
    while (it != adyacentes.end()) {
     if (it->destino == destino) {
        return true;
     }
    ++it;
    }
    return false;
}

template <class T>
int Nodo<T>::peso(Nodo<T>* destino) {
 typename list<Arista<T>>::iterator it = adyacentes.begin();
    while (it != adyacentes.end()) {
     if (it->destino == destino) {
      return it->peso;
     }
     ++it;
    }
    return -1;
}

template <class T>
int Nodo<T>::gradoSalida() {
    return adyacentes.size();
}
#endif
