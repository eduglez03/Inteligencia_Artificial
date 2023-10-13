#include<iostream>
#include <utility> // Necesario para std::pair

class Nodo {
  public:
    Nodo(std::pair<int, int>, int, int); // Constructor de la clase Nodo
    Nodo() {} // Constructor por defecto

    void set_coordenadas(std::pair<int, int>); // Setter coordenadas nodo en la matriz
    void set_heuristico(int); // Setter heuristico
    void set_coste(int); // Setter coste

    std::pair<int,int> get_coordenadas(); // Getter coordenadas nodo
    int get_heuristico(); // Getter heuristico
    int get_coste(); // Getter coste
    
  private:
    std::pair<int, int> Coordenadas_; // Coordenadas del nodo en la matriz
    int Heuristico_; // Distancia estimada al objeto
    int Coste_; // Coste acumulado para llegar a este nodo
};

// Constructor de la clase Nodo
Nodo::Nodo(std::pair<int, int> Coordenadas, int Coste, int Heuristico) {
  Coordenadas_ = Coordenadas;
  Coste_ = Coste;
  Heuristico_ = Heuristico;
}

// Setter coordenadas nodo en la matriz
void Nodo::set_coordenadas(std::pair<int, int> Coordenadas) {
  Coordenadas_ = Coordenadas;
}

// Setter heuristico
void Nodo::set_heuristico(int Heuristico) {
  Heuristico_ = Heuristico;
}

// Setter coste
void Nodo::set_coste(int Coste) {
  Coste_ = Coste;
}

// Getter coordenadas nodo
std::pair<int,int> Nodo::get_coordenadas() {
  return Coordenadas_;
}

// Getter heuristico
int Nodo::get_heuristico() {
  return Heuristico_;
}

// Getter coste
int Nodo::get_coste() {
  return Coste_;
}
    