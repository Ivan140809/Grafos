#ifndef NODO_H
#define NODO_H

#include <string>
#include <list>
using namespace std;

template <class T>
class Nodo;

template <class T>
struct Arista {
    Nodo<T>* destino;
    int peso;
    Arista(Nodo<T>* d, int p);
};

template <class T>
class Nodo {
private:
    T dato;
    list<Arista<T>> adyacentes;
    bool visitado;
    int nivel;

public:
  Nodo(T valor);
  T getDato();
  void setDato(T valor);
  bool getVisitado();
  void setVisitado(bool v);
  int getNivel();
  void setNivel(int n);
  list<Arista<T> >& getAdyacentes();
 void agregarAdyacente(Nodo<T>* destino, int peso);
  void eliminarAdyacente(Nodo<T>* destino);
  bool esAdyacente(Nodo<T>* destino);
  int peso(Nodo<T>* destino);
  int gradoSalida();
};

#include "Nodo.hxx"

#endif
