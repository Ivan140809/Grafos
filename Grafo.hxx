#ifndef GRAFO_HXX
#define GRAFO_HXX

#include <iostream>
#include <queue>
#include <stack>

template <class T>
Grafo<T>::Grafo(bool esDirigido) {
    dirigido = esDirigido;
}

template <class T>
Grafo<T>::~Grafo() {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        delete *it;
        ++it;
    }
    nodos.clear();
}

template <class T>
bool Grafo<T>::getDirigido() {
    return dirigido;
}

template <class T>
void Grafo<T>::setDirigido(bool d) {
    dirigido = d;
}

template <class T>
bool Grafo<T>::vacio() {
    return nodos.empty();
}

template <class T>
int Grafo<T>::tamano() {
    return nodos.size();
}

template <class T>
vector<Nodo<T>*>& Grafo<T>::getNodos() {
    return nodos;
}

template <class T>
void Grafo<T>::reiniciarVisitados() {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        (*it)->setVisitado(false);
        ++it;
    }
}

template <class T>
void Grafo<T>::reiniciarNiveles() {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        (*it)->setNivel(-1);
        ++it;
    }
}

template <class T>
Nodo<T>* Grafo<T>::buscarNodo(T valor) {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        if ((*it)->getDato() == valor) {
            return *it;
        }
        ++it;
    }
    return NULL;
}

template <class T>
bool Grafo<T>::existeNodo(T valor) {
    if (buscarNodo(valor) != NULL) {
        return true;
    }
    return false;
}

template <class T>
void Grafo<T>::agregarNodo(T valor) {
    if (existeNodo(valor)) {
        return;
    }
    Nodo<T>* nuevo = new Nodo<T>(valor);
    nodos.push_back(nuevo);
}

template <class T>
void Grafo<T>::eliminarNodo(T valor) {
    Nodo<T>* objetivo = buscarNodo(valor);
    if (objetivo == NULL) {
        return;
    }
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        (*it)->eliminarAdyacente(objetivo);
        ++it;
    }
    typename vector<Nodo<T>*>::iterator pos = nodos.begin();
    while (pos != nodos.end()) {
        if (*pos == objetivo) {
            nodos.erase(pos);
            break;
        }
        ++pos;
    }
    delete objetivo;
}

template <class T>
void Grafo<T>::agregarArista(T origen, T destino, int peso) {
    Nodo<T>* nodoOrigen = buscarNodo(origen);
    Nodo<T>* nodoDestino = buscarNodo(destino);
    if (nodoOrigen == NULL || nodoDestino == NULL) {
        return;
    }
    if (nodoOrigen->esAdyacente(nodoDestino)) {
        return;
    }
    nodoOrigen->agregarAdyacente(nodoDestino, peso);
    if (!dirigido) {
        nodoDestino->agregarAdyacente(nodoOrigen, peso);
    }
}

template <class T>
void Grafo<T>::eliminarArista(T origen, T destino) {
    Nodo<T>* nodoOrigen = buscarNodo(origen);
    Nodo<T>* nodoDestino = buscarNodo(destino);
    if (nodoOrigen == NULL || nodoDestino == NULL) {
        return;
    }
    nodoOrigen->eliminarAdyacente(nodoDestino);
    if (!dirigido) {
        nodoDestino->eliminarAdyacente(nodoOrigen);
    }
}

template <class T>
bool Grafo<T>::existeArista(T origen, T destino) {
    Nodo<T>* nodoOrigen = buscarNodo(origen);
    Nodo<T>* nodoDestino = buscarNodo(destino);
    if (nodoOrigen == NULL || nodoDestino == NULL) {
        return false;
    }
    return nodoOrigen->esAdyacente(nodoDestino);
}

template <class T>
int Grafo<T>::pesoArista(T origen, T destino) {
    Nodo<T>* nodoOrigen = buscarNodo(origen);
    Nodo<T>* nodoDestino = buscarNodo(destino);
    if (nodoOrigen == NULL || nodoDestino == NULL) {
        return -1;
    }
    return nodoOrigen->pesoHacia(nodoDestino);
}

template <class T>
int Grafo<T>::gradoSalida(T valor) {
    Nodo<T>* objetivo = buscarNodo(valor);
    if (objetivo == NULL) {
        return -1;
    }
    return objetivo->gradoSalida();
}

template <class T>
int Grafo<T>::gradoEntrada(T valor) {
    Nodo<T>* objetivo = buscarNodo(valor);
    if (objetivo == NULL) {
        return -1;
    }
    int contador = 0;
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        if ((*it)->esAdyacente(objetivo)) {
            contador = contador + 1;
        }
        ++it;
    }
    return contador;
}

template <class T>
int Grafo<T>::gradoTotal(T valor) {
    Nodo<T>* objetivo = buscarNodo(valor);
    if (objetivo == NULL) {
        return -1;
    }
    if (!dirigido) {
        return objetivo->gradoSalida();
    }
    return gradoSalida(valor) + gradoEntrada(valor);
}

template <class T>
void Grafo<T>::recorridoBFS(T inicio) {
    Nodo<T>* nodoInicio = buscarNodo(inicio);
    if (nodoInicio == NULL) {
        return;
    }
    reiniciarVisitados();
    queue<Nodo<T>*> cola;
    cola.push(nodoInicio);
    nodoInicio->setVisitado(true);
    while (!cola.empty()) {
        Nodo<T>* actual = cola.front();
        cola.pop();
        cout << actual->getDato() << " ";
        list<Arista<T>>& vecinos = actual->getAdyacentes();
        typename list<Arista<T>>::iterator it = vecinos.begin();
        while (it != vecinos.end()) {
            if (!it->destino->getVisitado()) {
                it->destino->setVisitado(true);
                cola.push(it->destino);
            }
            ++it;
        }
    }
    cout << endl;
}

template <class T>
void Grafo<T>::recorridoDFS(T inicio) {
    Nodo<T>* nodoInicio = buscarNodo(inicio);
    if (nodoInicio == NULL) {
        return;
    }
    reiniciarVisitados();
    stack<Nodo<T>*> pila;
    pila.push(nodoInicio);
    while (!pila.empty()) {
        Nodo<T>* actual = pila.top();
        pila.pop();
        if (!actual->getVisitado()) {
            actual->setVisitado(true);
            cout << actual->getDato() << " ";
            list<Arista<T>>& vecinos = actual->getAdyacentes();
            typename list<Arista<T>>::iterator it = vecinos.begin();
            while (it != vecinos.end()) {
                if (!it->destino->getVisitado()) {
                    pila.push(it->destino);
                }
                ++it;
            }
        }
    }
    cout << endl;
}

template <class T>
void Grafo<T>::recorridoPorNiveles(T inicio) {
    Nodo<T>* nodoInicio = buscarNodo(inicio);
    if (nodoInicio == NULL) {
        return;
    }
    reiniciarVisitados();
    reiniciarNiveles();
    queue<Nodo<T>*> cola;
    cola.push(nodoInicio);
    nodoInicio->setVisitado(true);
    nodoInicio->setNivel(0);
    int nivelActual = 0;
    cout << "Nivel 0: ";
    while (!cola.empty()) {
        Nodo<T>* actual = cola.front();
        cola.pop();
        if (actual->getNivel() > nivelActual) {
            nivelActual = actual->getNivel();
            cout << endl << "Nivel " << nivelActual << ": ";
        }
        cout << actual->getDato() << " ";
        list<Arista<T>>& vecinos = actual->getAdyacentes();
        typename list<Arista<T>>::iterator it = vecinos.begin();
        while (it != vecinos.end()) {
            if (!it->destino->getVisitado()) {
                it->destino->setVisitado(true);
                it->destino->setNivel(actual->getNivel() + 1);
                cola.push(it->destino);
            }
            ++it;
        }
    }
    cout << endl;
}

template <class T>
int Grafo<T>::nivelDeNodo(T inicio, T objetivo) {
    Nodo<T>* nodoInicio = buscarNodo(inicio);
    Nodo<T>* nodoObjetivo = buscarNodo(objetivo);
    if (nodoInicio == NULL || nodoObjetivo == NULL) {
        return -1;
    }
    reiniciarVisitados();
    reiniciarNiveles();
    queue<Nodo<T>*> cola;
    cola.push(nodoInicio);
    nodoInicio->setVisitado(true);
    nodoInicio->setNivel(0);
    while (!cola.empty()) {
        Nodo<T>* actual = cola.front();
        cola.pop();
        if (actual == nodoObjetivo) {
            return actual->getNivel();
        }
        list<Arista<T>>& vecinos = actual->getAdyacentes();
        typename list<Arista<T>>::iterator it = vecinos.begin();
        while (it != vecinos.end()) {
            if (!it->destino->getVisitado()) {
                it->destino->setVisitado(true);
                it->destino->setNivel(actual->getNivel() + 1);
                cola.push(it->destino);
            }
            ++it;
        }
    }
    return -1;
}
 
template <class T>
void Grafo<T>::recorridoPlano() {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        cout << (*it)->getDato() << " ";
        ++it;
    }
    cout << endl;
}
