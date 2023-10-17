#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>

#include "p02_nodo.h"
#include "laberinto.h"

class Astar {
  public:
    Astar(){} // Constructor por defecto

    // Getters
    std::set<Nodo> get_nodosCerrados() {return nodosCerrados_;}
    //std::priority_queue<Nodo> get_nodosAbiertos();

    // Setters
    void set_laberinto(std::vector<std::vector<int>> laberinto) { laberinto_ = laberinto; } 

    // Funcion
    bool obtenerCamino(std::pair<int, int>, std::pair<int, int>);
    Nodo menorCoste(std::set<Nodo> nodos);
    int CalcularHeuristico(const std::pair<int, int>& origen, const std::pair<int, int>& destino);
    std::vector<Nodo> GenerarHijos(Nodo& nodo);
    int CalularF(int heuristico, int coste);

  private:
    std::vector<std::vector<int>> laberinto_; // Laberinto
    std::set<Nodo> nodosCerrados_; // Lista de nodos cerrados
    std::set<Nodo> nodosAbiertos_; // Cola de nodos abiertos
    const int costeHV_ = 3; // Valor del coste horizontal y vertical
    const int costeDiagonal_ = 7; // Valor coste diagonal
};




// Metodo que calcula el heuristico del nodo
int Astar::CalcularHeuristico(const std::pair<int, int>& origen, const std::pair<int, int>& destino) {
  return std::abs(origen.first - destino.first) + std::abs(origen.second - destino.second);
}

// Obtener el nodo de menor coste de la lista de nodos abiertos
Nodo Astar::menorCoste(std::set<Nodo> nodos) {
  Nodo menor_coste;
  int coste{0};

  // Comparamos todos los nodos del set y buscamos el de menor coste
  for (auto nodo : nodos) {
    coste = nodo.get_funcionF();
    if(coste <= nodo.get_funcionF()) {
      menor_coste = nodo;
    }
  }

  return menor_coste;
}

// Metodo que calcula la funcion F
int Astar::CalularF(int heuristico, int coste) {
  return (heuristico + coste);
}



std::vector<Nodo> Astar::GenerarHijos(Nodo& nodo) {
  std::vector<std::pair<int, int>> movimientos = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

  const int horizontal_vertical = costeHV_;
  const int diagonal = costeDiagonal_;

  std::vector<Nodo> hijos;

  for (const auto& movimiento : movimientos) {
    int x = nodo.get_coordenadas().first + movimiento.first;
    int y = nodo.get_coordenadas().second + movimiento.second;

    if (x >= 0 && x < laberinto_.size() && y >= 0 && y < laberinto_[0].size() && laberinto_[x][y] == 0 &&
       (x != nodo.get_Coordenadaspadre().first || y != nodo.get_Coordenadaspadre().second)) {
      std::pair<int, int> nueva_coordenada = {x, y};
      const int nuevo_coste = (movimiento.first == 0 || movimiento.second == 0) ? horizontal_vertical : diagonal;
      Nodo nuevo_nodo(nueva_coordenada, 0, nodo.get_coste() + nuevo_coste, 0, nodo.get_coordenadas());
      hijos.push_back(nuevo_nodo);
    }
  }

  return hijos;
}


// Método para obtener el camino
bool Astar::obtenerCamino(std::pair<int, int> inicio, std::pair<int, int> destino) {
  // Creamos un nuevo nodo con las coordenadas del nodo inicial y final
  std::pair<int,int> coordenadas_padreInicio;
  coordenadas_padreInicio.first = -1;
  coordenadas_padreInicio.second = -1;
  Nodo Inicio(inicio,0,0,0, coordenadas_padreInicio);

  // Establecemos valores iniciales al primer nodo
  Inicio.set_heuristico(CalcularHeuristico(Inicio.get_coordenadas(), destino));
  Inicio.set_funcionF(Inicio.get_heuristico());

  // Añadimos el nodo Inicial a la lista de nodos abiertos
  nodosAbiertos_.insert(Inicio);

  while (!nodosAbiertos_.empty()) {
    Nodo coste_menor = menorCoste(nodosAbiertos_);

    // Comprobamos si el nodo actual es igual al final
    if (coste_menor.get_coordenadas() != destino) {
      // Generamos los hijos del nodo actual
      std::vector<Nodo> hijos = GenerarHijos(coste_menor); 
      
      // Evaluamos los hijos del nodo actual
      for (auto elemento : hijos) {
        elemento.set_heuristico(CalcularHeuristico(elemento.get_coordenadas(), destino));
        elemento.set_coste(elemento.get_coste() + coste_menor.get_coste());
        elemento.set_funcionF(CalularF(elemento.get_coste(), elemento.get_heuristico()));
      }

      // Añadimos los nodos hijos al vector de nodos abiertos
      for (auto nodos : hijos) {
        nodosAbiertos_.insert(nodos);
      }

      // Agregamos el nodo actual a la lista de nodos cerrados
      nodosCerrados_.insert(coste_menor);
      
      // Eliminamos el nodo de la lista de nodos abiertos
      auto iter = nodosAbiertos_.find(coste_menor);
      
      if (iter != nodosAbiertos_.end()) {
        // El valor está presente, y se elimina
        nodosAbiertos_.erase(iter);
      }

      for (auto nodo : nodosCerrados_) {
        std::cout << nodo.get_coordenadas().first << "  " << nodo.get_coordenadas().second << std::endl;
      }

    } else if (coste_menor.get_coordenadas() == destino) { // Si el nodo actual es igual al final se encontro el camino minimo
      Nodo Final(destino, coste_menor.get_coste(), 0, coste_menor.get_funcionF(), coste_menor.get_coordenadas());
      nodosAbiertos_.insert(Final);
      return true;
    }
  }
  
  // No se encontró un camino
  return false;
}



/*
// Metodo que genera los hijos de un nodo dado
std::vector<Nodo> Astar::GenerarHijos(Nodo nodo) {
  std::pair<int,int> movimiento1;
  std::pair<int,int> movimiento2;
  std::pair<int,int> movimiento3;
  std::pair<int,int> movimiento4;
  std::pair<int,int> movimiento5;
  std::pair<int,int> movimiento6;
  std::pair<int,int> movimiento7;
  std::pair<int,int> movimiento8;

  // Horizontal/Vertical
  movimiento1.first = -1;
  movimiento1.second = 0;

  // Diagonal
  movimiento2.first = -1;
  movimiento2.second = 1;
 
  // Horizontal/Vertical
  movimiento3.first = 0;
  movimiento3.second = 1;

  // Diagonal
  movimiento4.first = 1;
  movimiento4.second = 1;

  // Horizontal/Vertical
  movimiento5.first = 1;
  movimiento5.second = 0;

  // Diagonal
  movimiento6.first = 1;
  movimiento6.second = -1;

  // Horizontal/Vertical
  movimiento7.first = 0;
  movimiento7.second = -1;

  // Diagonal
  movimiento8.first = -1;
  movimiento8.second = -1;

  const int horizontal_vertical = 3;
  const int diagonal = 7;


  std::vector<Nodo> hijos;

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento1.first).at(nodo.get_coordenadas().second + movimiento1.second) == 0 && 
     (nodo.get_coordenadas().first + movimiento1.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento1.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento1.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento1.second;
    Nodo nuevo_nodo(nueva_coordenada, horizontal_vertical, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento2.first).at(nodo.get_coordenadas().second + movimiento2.second) == 0 && 
     (nodo.get_coordenadas().first + movimiento2.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento2.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento2.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento2.second;
    Nodo nuevo_nodo(nueva_coordenada, diagonal, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento3.first).at(nodo.get_coordenadas().second + movimiento3.second) == 0 &&
     (nodo.get_coordenadas().first + movimiento3.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento3.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento3.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento3.second;
    Nodo nuevo_nodo(nueva_coordenada, horizontal_vertical, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento4.first).at(nodo.get_coordenadas().second + movimiento4.second) == 0 &&
     (nodo.get_coordenadas().first + movimiento4.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento4.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento4.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento4.second;
    Nodo nuevo_nodo(nueva_coordenada, diagonal, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento5.first).at(nodo.get_coordenadas().second + movimiento5.second) == 0 &&
     (nodo.get_coordenadas().first + movimiento5.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento5.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento5.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento5.second;
    Nodo nuevo_nodo(nueva_coordenada, horizontal_vertical, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento6.first).at(nodo.get_coordenadas().second + movimiento6.second) == 0 &&
     (nodo.get_coordenadas().first + movimiento6.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento6.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento6.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento6.second;
    Nodo nuevo_nodo(nueva_coordenada, diagonal, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento7.first).at(nodo.get_coordenadas().second + movimiento7.second) == 0 &&
     (nodo.get_coordenadas().first + movimiento7.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento7.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento7.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento7.second;
    Nodo nuevo_nodo(nueva_coordenada, horizontal_vertical, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  if (laberinto_.at(nodo.get_coordenadas().first + movimiento8.first).at(nodo.get_coordenadas().second + movimiento8.second) == 0 &&
     (nodo.get_coordenadas().first + movimiento8.first != nodo.get_Coordenadaspadre().first && nodo.get_coordenadas().second + movimiento8.second != nodo.get_Coordenadaspadre().second)) {
    std::pair<int,int> nueva_coordenada;
    nueva_coordenada.first = nodo.get_coordenadas().first + movimiento8.first;
    nueva_coordenada.second = nodo.get_coordenadas().second + movimiento8.second;
    Nodo nuevo_nodo(nueva_coordenada, diagonal, 0, 0, nodo.get_coordenadas());
    hijos.push_back(nuevo_nodo);
  }

  return hijos;
}
*/
