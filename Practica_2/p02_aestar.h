#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>
#include <algorithm> // Para std::min_element
#include <cmath> // Para std::sqrt

#include "p02_nodo.h"
#include "laberinto.h"


// Enumerar las direcciones posibles:
enum direciones {A, AD, D, DB, B, BI, I, IA};

//Definimos vectores de desplazamientos para cada direccion;
//                            A    AB    D    DB    B    BI    I    IA
const short movimiento_i[] = {-1, -1,   0,    1,    1,   1,    0,   -1};
const short movimiento_j[] = {0,   1,   1,    1,    0,   -1,  -1,   -1};

class Astar {
  public:
    Astar() {}; // Constructor por defecto

    // Getters
    std::vector<Nodo> get_nodosCerrados() const {return nodosCerrados_;}
    std::vector<Nodo> get_nodosAbiertos() const { return nodosAbiertos_; }

    // Setters
    void set_laberinto(Laberinto laberinto) { laberinto_ = laberinto; } 


    // Funcion
    int Manhattan(const std::pair<int, int>& origen, const std::pair<int, int>& destino);
    int Euclidea(const std::pair<int, int>& origen, const std::pair<int, int>& destino);
    int CalularF(int heuristico, int coste);
    Nodo MenorCoste();
    bool ObtenerCamino(const std::pair<int, int>, const std::pair<int, int>, int heuristica);
    bool ComprobarAbiertos(const Nodo& nodo);
    bool ComprobarCerrados(const Nodo& nodo);
    bool ActualizarCoste(const Nodo& nodo);

  private:
    Laberinto laberinto_; // Laberinto
    std::vector<Nodo> nodosCerrados_; // Lista de nodos cerrados
    std::vector<Nodo> nodosAbiertos_; // Cola de nodos abiertos
    const int costeHV_ = 5; // Valor del coste horizontal y vertical
    const int costeDiagonal_ = 7; // Valor coste diagonal
};

// Obtener el nodo de menor coste de la lista de nodos abiertos
Nodo Astar::MenorCoste() {
  if (nodosAbiertos_.empty()) {
    throw std::runtime_error("La lista de nodos abiertos está vacía.");
  }

  Nodo minimo = nodosAbiertos_[0];
  size_t indiceMinimo = 0;

  for (size_t i = 1; i < nodosAbiertos_.size(); ++i) {
    if (nodosAbiertos_[i].get_funcionF() < minimo.get_funcionF()) {
      minimo = nodosAbiertos_[i];
      indiceMinimo = i;
    }
  }
  return minimo;
}

// Metodo que calcula el heuristico del nodo
int Astar::Manhattan(const std::pair<int, int>& origen, const std::pair<int, int>& destino) {
  const int constante{3};
  
  int distanciaHorizontal = std::abs(destino.first - origen.first);
  int distanciaVertical = std::abs(destino.second - origen.second);

  // Calcular la heurística de Manhattan con el factor de escala W
  int heuristica = (distanciaHorizontal + distanciaVertical) * constante;

  return heuristica;
}

// Metodo que calcula el heuristico del nodo
int Astar::Euclidea(const std::pair<int, int>& origen, const std::pair<int, int>& destino) {
  // Fórmula de la distancia euclidiana: sqrt((x2 - x1)^2 + (y2 - y1)^2)
  double distanciaX = destino.first - origen.first;
  double distanciaY = destino.second - destino.second;

  return std::sqrt(distanciaX * distanciaX + distanciaY * distanciaY);
}


// Metodo que calcula la funcion F
int Astar::CalularF(int heuristico, int coste) {
  return (heuristico + coste);
}

// Metodo que comprueba si el nodo ya esta en la lista de nodos cerrados
bool Astar::ComprobarCerrados(const Nodo& nodo) {
  for (int i = 0; i < nodosCerrados_.size(); i++) {
   if (nodosCerrados_[i].get_coordenadas() == nodo.get_coordenadas()) {
    return true;
   }
  }
  return false;
}





// Metodo que comprueba si el nodo ya esta en la lista de nodos abiertos
bool Astar::ComprobarAbiertos(const Nodo& nodo) {
  for (int i = 0; i < nodosAbiertos_.size(); i++) {
   if (nodosAbiertos_[i].get_coordenadas() == nodo.get_coordenadas()) {
    return true;
   }
  }
  return false;
}


// Metodo que actualiza la lista de nodos abiertos si el nodo que estamos analizando tiene un coste menor
// Metodo que actualiza la lista de nodos abiertos si el nood que estamos analizando tiene un coste menor
bool Astar::ActualizarCoste(const Nodo& nodo) {
  for (int i = 0; i < nodosAbiertos_.size(); i++) {
    if (nodosAbiertos_[i].get_coordenadas() == nodo.get_coordenadas()) {
      if (nodosAbiertos_[i] > nodo) {
        nodosAbiertos_[i] = nodo;
        return true;
      }
      return false;
    }
  }
  return false;
}



// Método para obtener el camino
bool Astar::ObtenerCamino(const std::pair<int, int> inicio, const std::pair<int, int> destino, int heuristica) {
  // Creamos un nuevo nodo con las coordenadas del nodo inicial y final
  std::pair<int,int> coordenadaspadre(-1,-1);
  Nodo Inicio(inicio,0,0,0, coordenadaspadre);

  // Establecemos valores iniciales al primer nodo
  if(heuristica == 1) {
    Inicio.set_heuristico(Manhattan(Inicio.get_coordenadas(), destino));
  }
  else if (heuristica == 2) {
    Inicio.set_heuristico(Euclidea(Inicio.get_coordenadas(), destino));
  }
  else {
    throw std::runtime_error("La heurística seleccionada no es válida.");
  }

  Inicio.set_funcionF(Inicio.get_heuristico());

  // Añadimos el nodo Inicial a la lista de nodos abiertos
  nodosAbiertos_.push_back(Inicio);

  
  // Mientras la lista de nodos abiertos no este vacia
  while (!nodosAbiertos_.empty()) {
    Nodo actual = MenorCoste(); // Obtenemos el nodo de menor coste de la lista de nodos abiertos
    //ActualizarCoste(actual);
    

    // Si el nodo actual es igual al final se encontro el camino minimo
    if (actual.get_coordenadas() == destino) { 
      nodosCerrados_.push_back(actual);
      return true;
    }

    // Calculamos los vecinos que tiene una posicion
    for (int dir = 0; dir < 8; dir++) {
      int nuevo_i = actual.get_coordenadas().first + movimiento_i[dir];
      int nuevo_j = actual.get_coordenadas().second + movimiento_j[dir];
      std::pair<int, int> sucesor_pos(nuevo_i, nuevo_j);

      if (sucesor_pos != actual.get_coordenadas()) {
        if (nuevo_i <= laberinto_.get_numFilas() && nuevo_j <= laberinto_.get_numColumnas() && nuevo_i >= 0 && nuevo_j >= 0) {
          if (laberinto_.get_laberinto()[nuevo_i][nuevo_j] != 1) {
            int g_sucesor = actual.get_coste() + ((dir % 2 == 0) ? 5 : 7);
            
            if(heuristica == 1) {
              int h_sucesor = Manhattan(sucesor_pos, destino);
              Nodo sucesor(sucesor_pos, g_sucesor, h_sucesor, g_sucesor + h_sucesor, actual.get_coordenadas());
              if (!ComprobarCerrados(sucesor) && !ActualizarCoste(sucesor)) {
                nodosAbiertos_.push_back(sucesor);
              }
            }
            else if (heuristica == 2) {
              int h_sucesor = Euclidea(sucesor_pos, destino);
              Nodo sucesor(sucesor_pos, g_sucesor, h_sucesor, g_sucesor + h_sucesor, actual.get_coordenadas());
              if (!ComprobarCerrados(sucesor) && !ActualizarCoste(sucesor)) {
                nodosAbiertos_.push_back(sucesor);
              }
            }
          }
        }
      }
    }

    // Agregamos el nodo actual a la lista de nodos cerrados
    if (!ComprobarCerrados(actual)) {
      std::cout << "Nodo actual: " << actual.get_coordenadas().first << ", " << actual.get_coordenadas().second << std::endl;
      nodosCerrados_.push_back(actual);
    }


    // Eliminamos el nodo actual de la lista de nodos abiertos
    for (auto iterador = nodosAbiertos_.begin(); iterador != nodosAbiertos_.end(); ++iterador) {
      if (iterador->get_coordenadas() == actual.get_coordenadas()) {
        nodosAbiertos_.erase(iterador);
        break;
      }
    }
  }
  
  // No se encontró un camino
  return false;
}





