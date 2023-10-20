#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>
#include <algorithm> // Para std::min_element

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
    bool ComprobarRango(const std::pair<int, int>& hijo);
    int CalcularHeuristico(const std::pair<int, int>& origen, const std::pair<int, int>& destino);
    int CalularF(int heuristico, int coste);
    Nodo MenorCoste();
    bool ObtenerCamino(const std::pair<int, int>, const std::pair<int, int>);
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

  //nodosAbiertos_.erase(nodosAbiertos_.begin() + indiceMinimo);

  return minimo;
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

// Metodo que calcula la funcion F
int Astar::CalularF(int heuristico, int coste) {
  return (heuristico + coste);
}






/*
// Función que comprueba si el siguiente movimiento se puede hacer
bool Astar::ComprobarRango(const std::pair<int, int>& hijo) {
  if ((laberinto_.get_laberinto()[hijo.first][hijo.second] == 1 && 
      (hijo.second > laberinto_.get_numColumnas() ||
      hijo.first > laberinto_.get_numFilas() ||
      hijo.second < 0 ||
      hijo.first < 0)) || laberinto_.get_laberinto()[hijo.first][hijo.second] == 1 ){
   std::cout << "Prueba" << std::endl;
    return false;
  }
  return true;
}
*/

// Función que comprueba si el siguiente movimiento se puede hacer
bool Astar::ComprobarRango(const std::pair<int, int>& hijo) {
  // Verificar si las coordenadas están dentro de los límites
  bool dentroDeLimites;
  if ((hijo.first >= 0 && hijo.first <= laberinto_.get_numFilas()) && (hijo.second >= 0 && hijo.second <= laberinto_.get_numColumnas())) {
    dentroDeLimites = true;
  } else {
    dentroDeLimites = false;
  }

  // La condición completa
  return dentroDeLimites;
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
bool Astar::ObtenerCamino(const std::pair<int, int> inicio, const std::pair<int, int> destino) {
  // Creamos un nuevo nodo con las coordenadas del nodo inicial y final
  std::pair<int,int> coordenadas_padreInicio;
  coordenadas_padreInicio.first = -1;
  coordenadas_padreInicio.second = -1;
  Nodo Inicio(inicio,0,0,0, coordenadas_padreInicio);

  // Establecemos valores iniciales al primer nodo
  Inicio.set_heuristico(CalcularHeuristico(Inicio.get_coordenadas(), destino));
  Inicio.set_funcionF(Inicio.get_heuristico());

  // Añadimos el nodo Inicial a la lista de nodos abiertos
  nodosAbiertos_.push_back(Inicio);

  
  // Mientras la lista de nodos abiertos no este vacia
  while (!nodosAbiertos_.empty()) {
    Nodo actual = MenorCoste(); // Obtenemos el nodo de menor coste de la lista de nodos abiertos

    // Si el nodo actual es igual al final se encontro el camino minimo
    if (actual.get_coordenadas() == destino) { 
      nodosCerrados_.push_back(actual);
      return true;
    }

    // Calculamos los vecinos que tiene una posicion
    for (int dir = A; dir < IA; dir++) {
      int nuevo_i = actual.get_coordenadas().first + movimiento_i[dir];
      int nuevo_j = actual.get_coordenadas().second + movimiento_j[dir];
      std::pair<int, int> sucesor_pos(nuevo_i, nuevo_j);

      if (nuevo_i <= laberinto_.get_numFilas() && nuevo_j <= laberinto_.get_numColumnas()) {
        if (laberinto_.get_laberinto()[nuevo_i][nuevo_j] != 1) {
          if (ComprobarRango(sucesor_pos)) {
            int g_sucesor = actual.get_coste() + ((dir % 2 == 0) ? 5 : 7);
            int h_sucesor = CalcularHeuristico(sucesor_pos, destino);
            Nodo sucesor(sucesor_pos, g_sucesor, h_sucesor, g_sucesor + h_sucesor, actual.get_coordenadas());

            nodosAbiertos_.push_back(sucesor);
            //if (!ActualizarCoste(sucesor) && !ComprobarCerrados(sucesor)) {
           // }
          }
        }
      }
    }

    // Agregamos el nodo actual a la lista de nodos cerrados
    if (!ComprobarCerrados(actual)) {
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





