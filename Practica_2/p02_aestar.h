#include<iostream>
#include<vector>

#include "p02_nodo.h"

class Astar {
  public:
    Astar() {} // Constructor por defecto

    std::vector<Nodo> get_NodosAbiertos(); // Getter nodos abiertos
    std::vector<Nodo> get_NodosCerrados(); // Getter nodos cerrados
    std::vector<std::vector<int>> get_matriz(); // Getter matriz

    void set_Matriz(std::vector<std::vector<int>>); // Setter matriz

    std::vector<Nodo> astar(); // Algoritmo A* 

  private:
    std::vector<Nodo> NodosAbiertos_;
    std::vector<Nodo> NodosCerrados_;
    std::vector<std::vector<int>> matriz_;
};


// Setter matriz
void Astar::set_Matriz(std::vector<std::vector<int>> matriz) {
  matriz_ = matriz;
}

// Getter nodos abiertos
std::vector<Nodo> Astar::get_NodosAbiertos() {
  return NodosAbiertos_;
}

// Getter nodos cerrados
std::vector<Nodo> Astar::get_NodosCerrados() {
  return NodosCerrados_;
}

// Getter matriz
std::vector<std::vector<int>> Astar::get_matriz() {
  return matriz_;
}