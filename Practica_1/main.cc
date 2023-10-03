#include<iostream>
#include<fstream>

#include "grafo.h"
#include "nodo.h"
#include "arbol.h"

/**
 * @brief Funcion que indica el funcionamiento del porgrama
 * 
 * @param argc 
 * @param argv 
 */
void Usage(int argc, char* argv[]) {
  if (argv[1] == "--help") {
    std::cout << "Este es un porgrama que calcula los caminos de un grafo para llegar desde un nodo inicial hasta un nodo final" << std::endl;
    std::exit(1);
  }
  if (argc != 2) {
    std::cout
        << "El programa necesita 2 argumentos. El ejecutable, el nodo inicio y el nombre del fihcero de entrada" << std::endl;
    std::exit(1);
  }
}

/**
 * @brief Funcion main, principal del programa
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) {
  
  Usage(argc, argv); // Función para comprobar si los parametros introducidos por el usuario son correctos

  int opcion_elegida{0}; // Opcion para determinar la operacion a realizar
  int nodo_inicial{0};
  int nodo_final{0};
  
  std::cout << "Determine la operación a realizar:\n\n"
            << "1. BFS\n"
            << "2. DFS\n" << std::endl;

  std::cin >> opcion_elegida;

  std::cout << "Seleccione el nodo inicial: " << std::endl;
  std::cin >> nodo_inicial;
  
  
  std::cout << "Seleccione el nodo final: " << std::endl;
  std::cin >> nodo_final;
  std::cout << std::endl;
  

  int total_nodos{0};

  std::ifstream archivo_entrada(argv[1]);  // Abrimos el fichero de entrada
  archivo_entrada >> total_nodos;  // Almacenamos el numero total de nodos

  Grafo graph; // Creamos un objeto de tipo Grafo
  Nodo* nodoInicial; // Creamos un onjeto de tipo Nodo, el cual será el nodo inicial
  Nodo* nodoFinal; // Creamos un onjeto de tipo Nodo, el cual será el nodo final
  double coste_final{0}; // Coste final

  graph.vectorResize(total_nodos + 1); // Hacemos un resize al vector que almacenara los punteros a los nodos del grafo

  // Almacenamos los distintos nodos del fichero en el vector de punteros a Nodos
  for (int i = 1; i <= total_nodos; i++) {
    for (int j = i + 1; j < total_nodos + 1; j++) {
      double coste;
      archivo_entrada >> coste;
      coste_final += coste;
      if (coste != -1.00) {
        if (graph.nodosGrafo_[i] == NULL) graph.nodosGrafo_[i] = new Nodo(i);
        if (graph.nodosGrafo_[j] == NULL) graph.nodosGrafo_[j] = new Nodo(j);
        graph.nodosGrafo_[j]->add_hijo(graph.nodosGrafo_[i]);
        graph.nodosGrafo_[i]->add_hijo(graph.nodosGrafo_[j]);
      }
    }
  }

  nodoInicial = graph.nodosGrafo_.at(nodo_inicial);
  nodoFinal = graph.nodosGrafo_.at(nodo_final);

  Arbol arbol; // Creamos un objeto de tipo arbol, el cual almacenará los arboles generados a partir del BFS y el DFS
  bool camino_encontrado = true;

  switch (opcion_elegida) {
    case 1: // BFS
      std::cout << "Este es el BFS: " << std::endl;
      camino_encontrado = graph.bfs(nodoInicial, nodoFinal, total_nodos, coste_final, arbol);
      
      if (camino_encontrado == false) {
        std::cout << "No se puedo encontrar un camino desde " << nodo_inicial << " hasta " << nodo_final << std::endl;
      }
      else if (camino_encontrado == true) {
        arbol.set_totalNodos(total_nodos);
        arbol.imprimirResultado();
      }
      break;
    case 2: // DFS
      std::cout << "Este es el DFS: " << std::endl;
      camino_encontrado = graph.dfs(nodoInicial, nodoFinal, total_nodos, coste_final, arbol);
      if (camino_encontrado == false) {
        std::cout << "No se puedo encontrar un camino desde " << nodo_inicial << " hasta " << nodo_final << "\n";
      }
      else if (camino_encontrado == true) {
        arbol.set_totalNodos(total_nodos);
        arbol.imprimirResultado();
      }
      break;
    default:
      std::cout << "Opción incorrecta" << std::endl;
      break;
  }
  return 0;
}
