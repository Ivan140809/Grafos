#include <iostream>
#include "includes/Grafo.h"

int main() {
    Grafo<int> g(false);
    g.agregarNodo(1);
    g.agregarNodo(2);
    g.agregarNodo(3);
    g.agregarNodo(4);
    g.agregarNodo(5);

    g.agregarArista(1, 2, 1);
    g.agregarArista(1, 3, 1);
    g.agregarArista(2, 4, 1);
    g.agregarArista(2, 5, 1);
    g.agregarArista(3, 4, 1);
    g.agregarArista(4, 5, 1);

    std::cout << "Recorrido BFS desde 1:" << std::endl;
    g.recorridoBFS(1);

    std::cout << "Recorrido DFS desde 1:" << std::endl;
    g.recorridoDFS(1);

    std::cout << "Recorrido por niveles desde 1:" << std::endl;
    g.recorridoPorNiveles(1);

    std::cout << "Recorrido plano:" << std::endl;
    g.recorridoPlano();
 
    std::cout << "Nivel de nodo 5 desde 1: " << g.nivelDeNodo(1, 5) << std::endl;

    std::cout << "Ejecutando Prim desde 1:" << std::endl;
    g.prim(1);

    std::cout << "Ejecutando Kruskal:" << std::endl;
    g.kruskal();

    std::cout << "Ejecutando Euler desde 1:" << std::endl;
    g.euler(1);

    std::cout << "Ejecutando Hamilton desde 1:" << std::endl;
    g.hamilton(1);

    return 0;
}
