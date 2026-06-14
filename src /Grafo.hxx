#ifndef GRAFO_HXX
#define GRAFO_HXX

#include "Grafo.h"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "Nodo.h"

using namespace std;

template <class T>
Grafo<T>::Grafo(bool esDirigido) {
    dirigido = esDirigido;
}

template <class T>
Grafo<T>::~Grafo() {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        delete *it;
        it++;
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
        it++;
    }
}

template <class T>
void Grafo<T>::reiniciarNiveles() {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
     (*it)->setNivel(-1);
     it++;
    }
}

template <class T>
Nodo<T>* Grafo<T>::buscarNodo(T valor) {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        if ((*it)->getDato() == valor) {
            return *it;
        }
        it++;
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
    while (it!=nodos.end()) {
        (*it)->eliminarAdyacente(objetivo);
        it++;
    }
    typename vector<Nodo<T>*>::iterator pos = nodos.begin();
    while (pos != nodos.end()) {
        if (*pos == objetivo) {
            nodos.erase(pos);
            break;
        }
        pos++;
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
    return nodoOrigen->peso(nodoDestino);
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
            it++;
        }
    }
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
                it++;
            }
        }
    }
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
            it++;
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
            it++;
        }
    }
    return -1;
}
 
template <class T>
void Grafo<T>::recorridoPlano() {
    typename vector<Nodo<T>*>::iterator it = nodos.begin();
    while (it != nodos.end()) {
        cout << (*it)->getDato() << " ";
        it++;
    }
}
template <class T>
void Grafo<T>::dikjstra(T origen, T destino) {
    int n = tamano();
    vector<int> distancias(n, INT_MAX);
    priority_queue<pair<int, Nodo<T>*>, vector<pair<int, Nodo<T>*>>, greater<pair<int, Nodo<T>*>>> pq;
    distancias[origen] = 0;
    pq.push({0, buscarNodo(origen)});
    int posOrigen= -1;
    for(int i =0;i<n;i++) { 
        if(nodos[i]->getDato() == origen) {
            posOrigen = i;
            break;
        }
    }
    if(posOrigen == -1) {
        cout << "El nodo de origen no existe." << endl;
        return;
    }

    while (!pq.empty()) {
     T u = pq.top().second->getDato();
     T d = pq.top().first;    
     pq.pop();
     if (u == destino) {
        cout << "Distancia más corta: " <<d<< endl;
        return;
     }
     if (d>distancias[u]) {
        continue;
     }
     for(int i = 0; i<n; i++) {
        T v = nodos[i]->getDato();
        if(existeArista(u,v)) {
            int peso = pesoArista(u,v);
            if(distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                pq.push({distancias[v], nodos[i]});
            }
        }
     }
     if (d == distancias[u]) {
     cout << "Nodo: " << u << "Distancia: " << d << endl;
     } 
    }
    cout << "No se encontró un camino desde " << origen << " hasta " << destino << endl;
}
template <class T>
void Grafo<T>::floydWarshall() {
    int n = tamano();
    vector<vector<int>> distancias(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++) {
        distancias[i][i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (existeArista(nodos[i]->getDato(), nodos[j]->getDato())) {
                distancias[i][j] = pesoArista(nodos[i]->getDato(), nodos[j]->getDato());
            }
        }
    }   
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distancias[i][k] != INT_MAX && distancias[k][j] != INT_MAX && distancias[i][k] + distancias[k][j] < distancias[i][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }
    cout << "Matriz de distancias más cortas" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (distancias[i][j] == INT_MAX) {
                cout << "no hay camino" << " ";
            } else {    
                cout << distancias[i][j] << " ";
            }
        }
        cout << endl;
    }
}

template <class T>
void Grafo<T>::prim(T inicio) {
    int n = tamano();
    vector<int> distancias(n, INT_MAX);
    vector<bool> enArbol(n, false);
    priority_queue<pair<int, Nodo<T>*>, vector<pair<int, Nodo<T>*>>, greater<pair<int, Nodo<T>*>>> pq;
    int costo = 0;
    pq.push({0, buscarNodo(inicio)});
    cout << "Aristas del arbol de expansión minima:" << endl;
    while (!pq.empty()) {
        T u = pq.top().second->getDato();
        int d = pq.top().first;
        pq.pop();
        int posU = -1;
        for (int i = 0; i < n; i++) {
            if (nodos[i]->getDato() == u) {
                posU = i;
                break;
            }
        }
        if (enArbol[posU]) {
            continue;
        }
        enArbol[posU] = true;
        costo += d;
        if (d != 0) {
            cout << "Nodo: " << u << " Costo: " << d << endl;
        }
        for (int i=0;i<n;i++) {
            if(!enArbol[i] && existeArista(u, nodos[i]->getDato())) {
                int peso = pesoArista(u, nodos[i]->getDato());
                if (peso<distancias[i]) {
                    distancias[i] = peso;
                    pq.push({peso, nodos[i]});
                }
            }
        }
    }
    cout << "Costo total del arbol de expansion minimaa: " << costo << endl;
}

template <class T>
void Grafo<T>::kruskal() {
    int n = tamano();
    if (n == 0) {
        cout << "Grafo vacío. Ninguna arista." << endl;
        return;
    }
    vector<tuple<int,int,int>> aristas;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (existeArista(nodos[i]->getDato(), nodos[j]->getDato())) {
                int peso = pesoArista(nodos[i]->getDato(), nodos[j]->getDato());
                aristas.push_back(make_tuple(peso, i, j));
            }
        }
    }
    sort(aristas.begin(), aristas.end());

    vector<int> padre(n);
    vector<int> rango(n, 0);
    for (int i = 0; i < n; ++i) padre[i] = i;

    int costo = 0;
    int aristasAgregadas = 0;
    cout << "Aristas del arbol de expansion minima con Kruskal:" << endl;
    for (size_t k = 0; k < aristas.size(); ++k) {
        if (aristasAgregadas == n - 1) break;
        int peso = std::get<0>(aristas[k]);
        int ui = std::get<1>(aristas[k]);
        int vi = std::get<2>(aristas[k]);

        int rx = ui;
        while (padre[rx] != rx) {
            padre[rx] = padre[padre[rx]];
            rx = padre[rx];
        }
        int ry = vi;
        while (padre[ry] != ry) {
            padre[ry] = padre[padre[ry]];
            ry = padre[ry];
        }

        if (rx != ry) {
            if (rango[rx] < rango[ry]) {
                padre[rx] = ry;
            } else if (rango[rx] > rango[ry]) {
                padre[ry] = rx;
            } else {
                padre[ry] = rx;
                rango[rx]++;
            }
            costo += peso;
            aristasAgregadas++;
            cout << "Nodo " << nodos[ui]->getDato() << " - Nodo " << nodos[vi]->getDato() << " Costo: " << peso << endl;
        }
    }
    if (aristasAgregadas != n - 1) {
        cout << "No se pudo construir un arbol de expansion minima." << endl;
    } else {
        cout << "Costo total del arbol de expansion minima: " << costo << endl;
    }
}


template <class T>
void Grafo<T>::euler(T inicio) {
    int n = tamano();
    vector<int> grado(n, 0);
    int aristas = 0;
    vector<vector<bool>> matrizAdyacencia(n, vector<bool>(n, false));
    int inicioPos = -1;
    for (int i = 0; i < n; i++) {
        if (nodos[i]->getDato() == inicio) {
            inicioPos = i;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (existeArista(nodos[i]->getDato(), nodos[j]->getDato())) {
                matrizAdyacencia[i][j] = true;
                grado[i]++;
                aristas++;
            }
        }
    }
    if(!this->dirigido){
        int totalAristas = aristas / 2;
    }
    int verticesImpares = 0;
    int nodoInicio = inicioPos;
    for (int i=0; i<n;i++) {
        if (grado[i] % 2 != 0) {
            verticesImpares++;
            if (nodoInicio == -1) {
                nodoInicio = i;
            }
        }
    }
    if (verticesImpares != 0 && verticesImpares != 2) {
        cout << "No existe un camino euleriano." << endl;
        return;
    }
    stack <int> pila;
    vector<int> camino;
    pila.push(nodoInicio);
    while (!pila.empty()) {
        int v=0;
        int u =pila.top();
        for (v=0; v<n; v++) {
            if (matrizAdyacencia[u][v]) {
                break;
            }
        }
        if (v==n) {
            camino.push_back(u);
            pila.pop();
        } else {
            matrizAdyacencia[u][v] = false;
            if (!this->dirigido) {
                matrizAdyacencia[v][u] = false;
            }
            pila.push(v);
        }

    }
    cout << "Camino Euleriano: ";
    for (int i = camino.size() - 1; i >= 0; i--) {
        cout << nodos[camino[i]]->getDato() << " ";
    }
    cout << endl;
}

template <class T>
void Grafo<T>::hamilton(T inicio) {
    int n = tamano();
    if (n == 0) {
        cout << "Grafo vacío." << endl;
        return;
    }
    int inicioPos = -1;
    for (int i = 0; i < n; i++) {
        if (nodos[i]->getDato() == inicio) {
            inicioPos = i;
            break;
        }
    }
    if (inicioPos == -1) {
        cout << "El nodo de inicio no existe." << endl;
        return;
    }
    stack<pair<int, vector<int>>> pila;
    vector<int> caminoInicial;
    caminoInicial.push_back(inicioPos);
    pila.push(make_pair(inicioPos, caminoInicial));

    while (!pila.empty()) {
        pair<int, vector<int>> estado = pila.top();
        pila.pop();
        int u = estado.first;
        vector<int> camino = estado.second;

        if (camino.size() == n) {
            cout << "Camino Hamiltoniano: ";
            for (int i = 0; i < camino.size(); i++) {
                cout << nodos[camino[i]]->getDato() << " ";
            }
            cout << endl;
            return;
        }

        for (int v = n - 1; v >= 0; v--) {
            bool estaEnCamino = false;
            for (int j = 0; j < camino.size(); j++) {
                if (camino[j] == v) {
                    estaEnCamino = true;
                    break;
                }
            }
            if (estaEnCamino) {
                continue;
            }
            if (existeArista(nodos[u]->getDato(), nodos[v]->getDato())) {
                vector<int> nuevoCamino = camino;
                nuevoCamino.push_back(v);
                pila.push(make_pair(v, nuevoCamino));
            }
        }
    }
    cout << "No se encontró un camino Hamiltoniano." << endl;
}
#endif