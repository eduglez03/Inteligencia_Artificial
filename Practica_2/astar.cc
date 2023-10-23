// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo p02_astar.cc: Archivo que contiene la implementación de las funciones de la clase Astar

#include "astar.h"

/**
 * @brief Función que obtiene el nodo de menor coste de la lista de nodos abiertos
*/
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

/**
 * @brief Función que calcula la heurística de Manhattan
*/
int Astar::Manhattan(const std::pair<int, int>& origen, const std::pair<int, int>& destino) {
  const int constante{3};
  
  int distanciaHorizontal = std::abs(destino.first - origen.first);
  int distanciaVertical = std::abs(destino.second - origen.second);

  // Calcular la heurística de Manhattan con el factor de escala W
  int heuristica = (distanciaHorizontal + distanciaVertical) * constante;

  return heuristica;
}

/**
 * @brief Función que calcula la heurística de Euclidea
*/
int Astar::Euclidea(const std::pair<int, int>& origen, const std::pair<int, int>& destino) {
  // Fórmula de la distancia euclidiana: sqrt((x2 - x1)^2 + (y2 - y1)^2)
  double distanciaX = destino.first - origen.first;
  double distanciaY = destino.second - destino.second;

  return std::sqrt(distanciaX * distanciaX + distanciaY * distanciaY);
}


/**
 * @brief Función que calcula la función F
*/
int Astar::CalularF(int heuristico, int coste) {
  return (heuristico + coste);
}

/**
 * @brief Función que comprueba si el nodo ya esta en la lista de nodos cerrados
*/
bool Astar::ComprobarCerrados(const Nodo& nodo) {
  for (int i = 0; i < nodosCerrados_.size(); i++) {
   if (nodosCerrados_[i].get_coordenadas() == nodo.get_coordenadas()) {
    return true;
   }
  }
  return false;
}

/**
 * @brief Función que comprueba si el nodo ya esta en la lista de nodos abiertos
*/
bool Astar::ComprobarAbiertos(const Nodo& nodo) {
  for (int i = 0; i < nodosAbiertos_.size(); i++) {
   if (nodosAbiertos_[i].get_coordenadas() == nodo.get_coordenadas()) {
    return true;
   }
  }
  return false;
}

/**
 * @brief Función que actualiza la lista de nodos abiertos si el nodo que estamos analizando tiene un coste menor
*/
bool Astar::ActualizarCoste(const Nodo& nodo) {
  for (int i = 0; i < nodosAbiertos_.size(); i++) {
    if (nodosAbiertos_[i].get_coordenadas() == nodo.get_coordenadas()) {
      if (nodosAbiertos_[i].get_funcionF() > nodo.get_funcionF()) {
        nodosAbiertos_.at(i) = nodo;
        return true;
      }
    }
  }
  return false;
}

/**
 * @brief Función que obtiene el camino
*/
bool Astar::ObtenerCamino(Laberinto& laberinto, int heuristica) {
  // Creamos un nuevo nodo con las coordenadas del nodo inicial y final
  std::pair<int,int> coordenadaspadre(-1,-1);
  Nodo Inicio(laberinto.get_posEntrada(),0,0,0, coordenadaspadre);

  // Establecemos valores iniciales al primer nodo
  if(heuristica == 1) {
    Inicio.set_heuristico(Manhattan(Inicio.get_coordenadas(), laberinto.get_posSalida()));
  }
  else if (heuristica == 2) {
    Inicio.set_heuristico(Euclidea(Inicio.get_coordenadas(), laberinto.get_posSalida()));
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
    if (actual.get_coordenadas() == laberinto.get_posSalida()) { 
      nodosCerrados_.push_back(actual);
      return true;
    }

    // Calculamos los vecinos que tiene una posicion
    for (int dir = 0; dir < 8; dir++) {
      int nuevo_i = actual.get_coordenadas().first + movimiento_i[dir];
      int nuevo_j = actual.get_coordenadas().second + movimiento_j[dir];
      std::pair<int, int> sucesor_pos(nuevo_i, nuevo_j);

      if (sucesor_pos != actual.get_coordenadas()) {
        if (nuevo_i <= laberinto.get_numFilas() && nuevo_j <= laberinto.get_numColumnas() && nuevo_i >= 0 && nuevo_j >= 0) {
          if (laberinto.get_laberinto()[nuevo_i][nuevo_j] != 1) {
            int g_sucesor = actual.get_coste() + ((dir % 2 == 0) ? 5 : 10);
            
            if(heuristica == 1) {
              int h_sucesor = Manhattan(sucesor_pos, laberinto.get_posSalida());
              Nodo sucesor(sucesor_pos, g_sucesor, h_sucesor, g_sucesor + h_sucesor, actual.get_coordenadas());
              if (!ComprobarCerrados(sucesor) && !ComprobarAbiertos(sucesor)) {
                nodosAbiertos_.push_back(sucesor);
              } else {
                ActualizarCoste(sucesor);
              }
            }
            else if (heuristica == 2) {
              int h_sucesor = Euclidea(sucesor_pos, laberinto.get_posSalida());
              Nodo sucesor(sucesor_pos, g_sucesor, h_sucesor, g_sucesor + h_sucesor, actual.get_coordenadas());
              if (!ComprobarCerrados(sucesor) && !ComprobarAbiertos(sucesor)) {
                nodosAbiertos_.push_back(sucesor);
              } else {
                ActualizarCoste(sucesor);
              }
            }
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