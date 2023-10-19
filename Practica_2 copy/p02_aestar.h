#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>
#include <algorithm> // Para std::min_element

#include "p02_nodo.h"
#include "laberinto.h"

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
    std::vector<Nodo*> obtenerHijos(const std::pair<int, int>& coordenadas);
    int CalularF(int heuristico, int coste);
    bool comprobarRango(int fila, int columna, int filas, int columnas);
    void Visitar(int x, int y);
    bool Visitados(int x, int y);

  private:
    Laberinto laberinto_; // Laberinto
    std::vector<Nodo*> nodosCerrados_; // Lista de nodos cerrados
    std::vector<Nodo*> nodosAbiertos_; // Cola de nodos abiertos
    const int costeHV_ = 5; // Valor del coste horizontal y vertical
    const int costeDiagonal_ = 7; // Valor coste diagonal
};

// Metodo que comprueba si una coordenada esta dentro del rango de la matriz
bool Astar::comprobarRango(int fila, int columna, int filas, int columnas) {
  return (fila >= 0 && fila < filas && columna >= 0 && columna < columnas);
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

// Método para obtener las coordenadas adyacentes
std::vector<Nodo*> Astar::obtenerHijos(const std::pair<int, int>& coordenadas) {
  std::vector<Nodo*> adyacentes;

  // Definir las direcciones posibles: arriba, abajo, izquierda, derecha, diagonal superior izquierda, diagonal superior derecha, diagonal inferior izquierda, diagonal inferior derecha
  int direcciones[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

  // Obtener las coordenadas adyacentes
  for (const auto& direccion : direcciones) {
    int nuevaFila = coordenadas.first + direccion[0];
    int nuevaColumna = coordenadas.second + direccion[1];

    // No se puede volver a la posicion anterior
    if (nuevaFila != 0 && nuevaColumna != 0) {
      // No se puede acceder a una posicion con un obstaculo
      if(laberinto_.get_laberinto()[nuevaFila][nuevaColumna] != 1) {
        // Verificar si las nuevas coordenadas están dentro del rango de la matriz
        if (comprobarRango(nuevaFila, nuevaColumna, laberinto_.get_numFilas(), laberinto_.get_numColumnas())) {
          if (direccion == direcciones[0] || direccion == direcciones[1] || direccion == direcciones[2] || direccion == direcciones[3]) {
            if (Visitados(nuevaFila, nuevaColumna)) {
              Nodo* nuevo_nodo = new Nodo(std::make_pair(nuevaFila, nuevaColumna), costeHV_, 0, 0, coordenadas);
              adyacentes.push_back(nuevo_nodo);
              Visitar(nuevaFila, nuevaColumna);
            }
          } else {
              if (Visitados(nuevaFila, nuevaColumna)) {
                Nodo* nuevo_nodo = new Nodo(std::make_pair(nuevaFila, nuevaColumna), costeDiagonal_, 0, 0, coordenadas);
                adyacentes.push_back(nuevo_nodo);
                Visitar(nuevaFila, nuevaColumna);
              }
          }
          //std::cout << "Coordenadas: " << nuevaFila << " " << nuevaColumna << std::endl;
        }
      } 
    } 
  }

  return adyacentes;
}



void Astar::Visitar(int x, int y) {
  laberinto_.visitar(x, y);
}



bool Astar::Visitados(int x, int y) {
  return laberinto_.es_Visitado(x, y);
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








// Método para obtener el camino
bool Astar::obtenerCamino(std::pair<int, int> inicio, std::pair<int, int> destino) {
  // Creamos un nuevo nodo con las coordenadas del nodo inicial y final
  std::pair<int,int> coordenadas_padreInicio;
  coordenadas_padreInicio.first = -1;
  coordenadas_padreInicio.second = -1;
  Nodo* Inicio = new Nodo(inicio,0,0,0, coordenadas_padreInicio);

  // Establecemos valores iniciales al primer nodo
  Inicio->set_heuristico(CalcularHeuristico(Inicio->get_coordenadas(), destino));
  Inicio->set_funcionF(Inicio->get_heuristico());

  // Añadimos el nodo Inicial a la lista de nodos abiertos
  nodosAbiertos_.push_back(Inicio);

  while (!nodosAbiertos_.empty()) {
    Nodo* coste_menor = menorCoste(nodosAbiertos_);
    
    if (coste_menor->get_coordenadas() == destino) { // Si el nodo actual es igual al final se encontro el camino minimo
      Nodo* Final = new Nodo(destino, coste_menor->get_coste(), 0, coste_menor->get_funcionF(), coste_menor->get_coordenadas());
      nodosCerrados_.push_back(Final);
      return true;
    }

    // Comprobamos si el nodo actual es igual al final
    // Generamos los hijos del nodo actual
    std::vector<Nodo*> hijos = obtenerHijos(coste_menor->get_coordenadas()); 
    for(auto& elemento : hijos) {
      std::cout << elemento->get_coordenadas().first << " " << elemento->get_coordenadas().second << std::endl;
    }

    // Evaluamos los hijos del nodo actual
    for (auto& elemento : hijos) {
      elemento->set_heuristico(CalcularHeuristico(elemento->get_coordenadas(), destino));
      elemento->set_coste(elemento->get_coste() + coste_menor->get_coste());
      elemento->set_funcionF(CalularF(elemento->get_heuristico(), elemento->get_coste()));
      //std::cout << "(" << elemento.get_coordenadas().first << "," << elemento.get_coordenadas().second << ")   " <<  "   Heuristico: " << elemento.get_heuristico() << "   Coste: " << elemento.get_coste() << "   Funcion F: " << elemento.get_funcionF() << std::endl;
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