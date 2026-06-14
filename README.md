# Grafos

Este proyecto implementa una estructura de grafo genérico en C++ con algoritmos de recorrido determinados en el grafo.

## Estructura del proyecto

- `includes/Grafo.h`: declaracion de la clase `Grafo` y sus métodos.
- `includes/Nodo.h`: declaracion de la clase `Nodo` y la estructura `Arista`.
- `src /Grafo.hxx`: implementacion de los algoritmos del grafo.
- `src /Nodo.hxx`: implementacion de la clase `Nodo`.

## Algoritmos soportados
### Recorridos

- `recorridoBFS(T inicio)`: busca en anchura desde el nodo de inicio.
- `recorridoDFS(T inicio)`: busca en profundidad desde el nodo de inicio.
- `recorridoPorNiveles(T inicio)`: recorre por niveles (nivel 0, nivel 1, etc.).
- `recorridoPlano()`: imprime todos los nodos guardados en el grafo sin un orden determinado .

### Consultas y propiedades
- `buscarNodo(T valor)`: devuelve el nodo que contiene el valor dado.
- `existeNodo(T valor)`: verifica si existe un nodo con ese valor.
- `existeArista(T origen, T destino)`: verifica si existe una arista entre dos nodos.
- `pesoArista(T origen, T destino)`: retorna el peso de la arista entre origen y destino.
- `gradoSalida(T valor)`: grado de salida de un nodo.
- `gradoEntrada(T valor)`: grado de entrada de un nodo.
- `gradoTotal(T valor)`: grado total del nodo.
- `nivelDeNodo(T inicio, T objetivo)`: calcula la distancia en niveles entre dos nodos.

### Caminos y algoritmos de optimizacion
- `dikjstra(T origen, T destino)`: implementa Dijkstra para encontrar el camino de menor peso entre dos nodos.
- `floydWarshall()`: ejecuta el algoritmo de Floyd-Warshall para distancias entre todos los pares de nodos.
- `prim(T inicio)`: construye un árbol de expansión mínima usando Prim.
- `kruskal()`: construye un árbol de expansión mínima con Kruskal.
- `euler(T inicio)`: busca un camino euleriano a partir de un nodo inicial.
- `hamilton(T inicio)`: busca un camino Hamiltoniano usando un recorrido iterativo con pila.

## Cómo usar
1. Incluye `includes/Grafo.h` en tu programa.
2. Crea un grafo: `Grafo<int> g(false);` o `Grafo<string> g(true);`.
3. Agrega nodos y aristas:
   ```cpp
   g.agregarNodo(1);
   g.agregarNodo(2);
   g.agregarArista(1, 2, 5);
   ```
4. Ejecuta los recorridos:
   ```cpp
   g.recorridoBFS(1);
   g.recorridoDFS(1);
   g.recorridoPorNiveles(1);
   g.recorridoPlano();
   ```
5. Ejecuta algoritmos especiales:
   ```cpp
   g.prim(1);
   g.kruskal();
   g.euler(1);
   g.hamilton(1);
   ```

## Compilacion

Compila con C++17, incluyendo el directorio `includes`:

```bash
g++ -std=c++17 -I. main.cpp -o main
```

Asegúrate de que tu archivo principal incluya `includes/Grafo.h`.

## Notas

- El código usa plantillas para permitir distintos tipos de datos en los nodos.
- El grafo puede ser dirigido o no dirigido según el valor pasado al constructor.
- Las implementaciones de `kruskal()` y `hamilton()` usan estrategias iterativas.
