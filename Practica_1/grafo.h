#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "nodo.h"
#include "arbol.h"

/**
 * @brief Declaracion de la clase Grafo
 * 
 */
class Grafo {
 public:
  Grafo(){}; // Constructor por defecto

  bool bfs(Nodo* inicial, Nodo* final, int, double, Arbol&); // BFS
  bool dfs (Nodo* iniicial, Nodo* final, int, double, Arbol&); //DFS
  Nodo* get_nodo(int); // Getter nodo

  void vectorResize(int); // Resize vector nodos
  std::vector<Nodo*> nodosGrafo_; // Vector nodos grafo

  bool EsPadre(Nodo*, Nodo*); // Metodo que compurbe si un nodo es padre de otro
  Nodo* CrearNodo(Nodo*);  // Metodo que crea un nuevo nodo
};