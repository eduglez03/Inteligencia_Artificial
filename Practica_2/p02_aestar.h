#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>
#include <algorithm> // Para std::min_element

#include "p02_nodo.h"
#include "laberinto.h"


enum movimientos {A, AD, D, DB, B, BI, I, IA};
const short movimiento_i[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const short movimiento_j[] = {0, 1, 1, 1, 0, -1, -1, -1};


class Astar {
  public:
    Astar() {}; // Constructor por defecto

    // Getters
    std::vector<Nodo*> get_nodosCerrados() {return nodosCerrados_;}
    std::vector<Nodo*> get_nodosAbiertos() { return nodosAbiertos_; }

    // Setters
    void set_laberinto(Laberinto laberinto) { laberinto_ = laberinto; } 

    // Funcion
    bool obtenerCamino(std::pair<int, int>, std::pair<int, int>);
    Nodo* menorCoste(const std::vector<Nodo*>& nodos);
    int CalcularHeuristico(const std::pair<int, int>& origen, const std::pair<int, int>& destino);
    std::vector<Nodo*> obtenerHijos(Nodo* padre);
    int CalularF(int heuristico, int coste);
    bool comprobarRango(std::pair<int,int> hijo);
    bool ActualizarCoste(Nodo* nodo);
    bool AnalizarCerrados(Nodo* nodo);

  private:
    Laberinto laberinto_; // Laberinto
    std::vector<Nodo*> nodosCerrados_; // Lista de nodos cerrados
    std::vector<Nodo*> nodosAbiertos_; // Cola de nodos abiertos
    const int costeHV_ = 5; // Valor del coste horizontal y vertical
    const int costeDiagonal_ = 7; // Valor coste diagonal
};

// Metodo que comprueba si una coordenada esta dentro del rango de la matriz
bool Astar::comprobarRango(std::pair<int,int> hijo) {

  if(laberinto_.get_laberinto().at(hijo.first).at(hijo.second) == 1 || hijo.second >= laberinto_.get_numColumnas() || hijo.first >= laberinto_.get_numFilas() || hijo.second < 0 || hijo.first < 0) {
    return false;
  } else {
    return true;
  }
}

// Metodo que calcula la funcion F
int Astar::CalularF(int heuristico, int coste) {
  return (heuristico + coste);
}

// Metodo que calcula el heuristico del nodo
int Astar::CalcularHeuristico(const std::pair<int, int>& origen, const std::pair<int, int>& destino) {
  const int constante{3};
  
  int distanciaHorizontal = std::abs(destino.first - origen.first);
  int distanciaVertical = std::abs(destino.second - origen.second);

  // Calcular la heurística de Manhattan con el factor de escala W
  int heuristica = (distanciaHorizontal + distanciaVertical) * constante;

  return heuristica;
}

// Obtener el nodo de menor coste de la lista de nodos abiertos
Nodo* Astar::menorCoste(const std::vector<Nodo*>& nodos) {
  // Utilizar std::min_element con un comparador personalizado
  auto comparador = [](Nodo* a, Nodo* b) {
    return a->get_funcionF() < b->get_funcionF();
  };

  Nodo* menor = *std::min_element(nodos.begin(), nodos.end(), comparador);

  return menor;
}





bool Astar::ActualizarCoste(Nodo* nodo) {
  for(int i = 0; i < nodosAbiertos_.size(); i++) {
    if(nodosAbiertos_.at(i) == nodo) {
      if(nodosAbiertos_.at(i)->get_funcionF() > nodo->get_funcionF()) {
        nodosAbiertos_.at(i) = nodo;
        return true;
      }
      return false;
    }
  }
  return false;
}




bool Astar::AnalizarCerrados(Nodo* nodo) {
  for(int i = 0; i < nodosCerrados_.size(); i++) {
    if(nodosCerrados_.at(i) == nodo) {
      return true;
    }
  }
  return false;
}









// Método para obtener las coordenadas adyacentes
std::vector<Nodo*> Astar::obtenerHijos(Nodo* padre) {
  std::vector<Nodo*> adyacentes;

  // Obtener las coordenadas adyacentes
  for (int i = A; i < IA; i++) {
    int nuevaFila = padre->get_coordenadas().first + movimiento_i[i];
    int nuevaColumna = padre->get_coordenadas().second + movimiento_j[i];
    
    std::pair<int,int> hijo(nuevaFila, nuevaColumna);

    // No se puede volver a la posicion anterior
    if (hijo != padre->get_coordenadas()) {
      if (comprobarRango(hijo)) {
        if (i % 2 == 0) {
          int g_susesores = padre->get_coste() + costeHV_;
          Nodo* nuevo_nodo = new Nodo(std::make_pair(nuevaFila, nuevaColumna), g_susesores, 0, 0, padre->get_coordenadas(), true);
          if (ActualizarCoste(nuevo_nodo) == false && AnalizarCerrados(nuevo_nodo) == false) {
            adyacentes.push_back(nuevo_nodo);
          }
        }
        else if (i % 2 != 0){
          int g_susesores = padre->get_coste() + costeDiagonal_;
          Nodo* nuevo_nodo = new Nodo(std::make_pair(nuevaFila, nuevaColumna), g_susesores, 0, 0, padre->get_coordenadas(), true);
          if (ActualizarCoste(nuevo_nodo) == false && AnalizarCerrados(nuevo_nodo) == false) {
            adyacentes.push_back(nuevo_nodo);
          }
        }
      }
    }
  }
  return adyacentes;
}




// Método para obtener el camino
bool Astar::obtenerCamino(std::pair<int, int> inicio, std::pair<int, int> destino) {
  // Creamos un nuevo nodo con las coordenadas del nodo inicial y final
  std::pair<int,int> coordenadas_padreInicio;
  coordenadas_padreInicio.first = -1;
  coordenadas_padreInicio.second = -1;
  Nodo* Inicio = new Nodo(inicio,0,0,0, coordenadas_padreInicio, true);

  // Establecemos valores iniciales al primer nodo
  Inicio->set_heuristico(CalcularHeuristico(Inicio->get_coordenadas(), destino));
  Inicio->set_funcionF(Inicio->get_heuristico());

  // Añadimos el nodo Inicial a la lista de nodos abiertos y visitados
  nodosAbiertos_.push_back(Inicio);

  while (!nodosAbiertos_.empty()) {
    Nodo* coste_menor = menorCoste(nodosAbiertos_);
    
    if (coste_menor->get_coordenadas() == destino) { // Si el nodo actual es igual al final se encontro el camino minimo
      Nodo* Final = new Nodo(destino, coste_menor->get_coste(), 0, coste_menor->get_funcionF(), coste_menor->get_coordenadas(), true);
      nodosCerrados_.push_back(Final);
      return true;
    }

    // Comprobamos si el nodo actual es igual al final
    // Generamos los hijos del nodo actual
    std::vector<Nodo*> hijos = obtenerHijos(coste_menor); 

    // Evaluamos los hijos del nodo actual
    for (auto& elemento : hijos) {
      elemento->set_heuristico(CalcularHeuristico(elemento->get_coordenadas(), destino));
      elemento->set_funcionF(elemento->get_coste() + elemento->get_heuristico());
    }

    // Añadimos los nodos hijos al vector de nodos abiertos
    for (auto& nodos : hijos) {
      nodosAbiertos_.push_back(nodos);
    }

    // Agregamos el nodo actual a la lista de nodos cerrados
    nodosCerrados_.push_back(coste_menor);

    // Eliminamos el nodo de la lista de nodos abiertos
    std::vector<Nodo*> auxiliar;
    auxiliar = nodosAbiertos_;
    nodosAbiertos_.clear();

    for (int i = 0; i < auxiliar.size(); i++) {
      if (auxiliar.at(i) == coste_menor) {
        continue;
      } else {
        nodosAbiertos_.push_back(auxiliar.at(i));
      }
    }
  }
  
  // No se encontró un camino
  return false;
}