#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>

#include "p02_nodo.h"
#include "laberinto.h"

class Astar {
  public:
    Astar(Laberinto laberinto) {laberinto_ = laberinto;} // Constructor de la clase

    // Getters
    std::set<Nodo> get_nodosCerrados() {return nodosCerrados_;}
    //std::priority_queue<Nodo> get_nodosAbiertos();

    // Fuuncion
    bool obtenerCamino(std::pair<int, int>, std::pair<int, int>);

  private:
    Laberinto laberinto_; // Laberinto
    std::set<Nodo> nodosCerrados_; // Lista de nodos cerrados
    std::priority_queue<Nodo, std::vector<Nodo>, ComparadorNodo> nodosAbiertos_; // Cola de nodos abiertos
    const int costeHV_ = 3; // Valor del coste horizontal y vertical
    const int costeDiagonal_ = 7; // Valor coste diagonal
};

// Definir un comparador para ordenar los nodos por coste de menor a mayor
struct ComparadorNodo {
  bool operator()(Nodo nodo1, Nodo nodo2) const {
    return nodo1.get_coste() > nodo2.get_coste();
  }
};




// Método para obtener el camino
bool Astar::obtenerCamino(std::pair<int, int> inicio, std::pair<int, int> destino) {
  // Creamos un nuevo nodo con las coordenadas del nodo inicial y final
  Nodo Inicio(inicio,0,0);
  Nodo Final(destino,0,0);

  // Añadimos el nodo Inicial a la lista de nodos abiertos
  nodosAbiertos_.push(Inicio);

  while (!nodosAbiertos_.empty()) {
    Nodo coste_menor = nodosAbiertos_.top();
    nodosAbiertos_.pop();

    // Comprobamos si el nodo actual es igual al final
    if (coste_menor.get_coordenadas() != Final.get_coordenadas()) {
      // Generamos los hijos del nodo actual
      std::vector<Nodo> hijos = generarHijos(coste_menor); 
      
      // Evaluamos los hijos del nodo actual
      for (auto elemento : hijos) {
        elemento.get_coste();
        elemento.set_heuristico();
      }

      // Añadimos los nodos hijos al vector de nodos abiertos
      for (auto nodos : hijos) {
        nodosAbiertos_.push(nodos);
      }

      // Agregamos el nodo actual a la losta de nodos cerrados
      nodosCerrados_.insert(coste_menor);
    } else if (coste_menor.get_coordenadas() == Final.get_coordenadas()) { // Si el nodo actual es igual al final se encontro el camino minimo
      return true;
    }
  }
  
  // No se encontró un camino
  return false;
}
















/*
  // Reiniciar listas de nodos
  nodosAbiertos_ = std::priority_queue<Nodo>();
  nodosCerrados_.clear();

  // Crear nodo inicial
  Nodo nodoInicio(inicio, 0, 0);
  nodoInicio.set_heuristico(nodoInicio.calcular_heuristico_manhattan(destino));

  // Agregar nodo inicial a nodos abiertos
  nodosAbiertos_.push(nodoInicio);

  while (!nodosAbiertos_.empty()) {
    // Obtener el nodo con menor coste estimado
    Nodo nodoActual = nodosAbiertos_.top();
    nodosAbiertos_.pop();

    // Verificar si llegamos al destino
    if (nodoActual.get_coordenadas() == destino) {
      
      
      
      // Reconstruir el camino desde el nodo de destino hasta el inicio
      std::vector<Nodo> camino;
      while (nodoActual.get_coordenadas() != inicio) {
        camino.push_back(nodoActual);
        nodoActual = nodoActual.get_padre();
      }
      // Agregar el nodo de inicio al camino
      camino.push_back(nodoInicio);

      // Invertir el camino ya que fue construido desde el destino hacia el inicio
      std::reverse(camino.begin(), camino.end());

      return camino;
    }




    // Agregar nodo actual a nodos cerrados
    nodosCerrados_.insert(nodoActual);

    // Expandir nodos vecinos
    expandirNodosVecinos(nodoActual, destino);
  }
*/