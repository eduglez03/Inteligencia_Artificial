#include<iostream>
#include <utility> // Necesario para std::pair

class Nodo {
  public:
    Nodo(std::pair<int, int>, double, int); // Constructor de la clase Nodo
    Nodo() {} // Constructor por defecto

    bool operator>(const Nodo&) const; // Sobrecarga operador > para comparar nodos

  private:
    std::pair<int, int> Coordenadas_; // Coordenadas del nodo en la matriz
    double Coste_; // Coste acumulado para llegar a este nodo
    int Heuristico_; // Distancia estimada al objeto

};

// Constructor de la clase Nodo
Nodo::Nodo(std::pair<int, int> Coordenadas, double Coste, int Heuristico) {
  Coordenadas_ = Coordenadas;
  Coste_ = Coste;
  Heuristico_ = Heuristico;
}

// Sobrecarga operador > para comparar nodos
bool Nodo::operator>(const Nodo& nodo) const {
  return Coste_ + Heuristico_ > nodo.Coste_ + nodo.Heuristico_;
}