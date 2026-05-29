#ifndef GRAFO_H
#define GRAFO_H

#include <vector>

using namespace std;

template <class T>
class Grafo {
private:
    vector<Nodo<T>*> nodos;
    bool dirigido;
    void reiniciarVisitados();
    void reiniciarNiveles();
public:
    Grafo(bool esDirigido);
    ~Grafo();
    bool getDirigido();
    void setDirigido(bool d);
    bool vacio();
    int tamano();
    vector<Nodo<T>*>& getNodos();
    Nodo<T>* buscarNodo(T valor);
    bool existeNodo(T valor);
    void agregarNodo(T valor);
    void eliminarNodo(T valor);
    void agregarArista(T origen, T destino, int peso);
    void eliminarArista(T origen, T destino);
    bool existeArista(T origen, T destino);
    int pesoArista(T origen, T destino);
    int gradoSalida(T valor);
    int gradoEntrada(T valor);
    int gradoTotal(T valor);
    void recorridoBFS(T inicio);
    void recorridoDFS(T inicio);
    void recorridoPorNiveles(T inicio);
    int nivelDeNodo(T inicio, T objetivo);
    void recorridoPlano();
};

#include Grafo.hxx;
#endif
