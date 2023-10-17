#include<iostream>
#include <utility> // Necesario para std::pair

class Nodo {
  public:
    Nodo(std::pair<int, int>, int, int, int, std::pair<int,int>); // Constructor de la clase Nodo
    Nodo() {} // Constructor por defecto

    void set_coordenadas(std::pair<int, int> coordenadas) { Coordenadas_ = coordenadas; } // Setter coordenadas nodo en la matriz
    void set_heuristico(int heuristico) { Heuristico_ = heuristico; } // Setter heuristico
    void set_coste(int coste) { Coste_ = coste; } // Setter coste
    void set_padre(std::pair<int,int> padre) { CoordenadasPadre_ = padre; } // Setter padre
    void set_funcionF(int funcionF) { FuncionF_ = funcionF; } // Setter funcion f

    std::pair<int,int> get_coordenadas() const { return Coordenadas_; } // Getter coordenadas nodo
    int get_heuristico() const { return Heuristico_; } // Getter heuristico
    int get_coste() { return Coste_; } // Getter coste
    int get_funcionF() { return FuncionF_; } // Getter funcion f
    std::pair<int,int> get_Coordenadaspadre() { return CoordenadasPadre_; } // Getter padre

    // Sobrecarga del operador <
    bool operator<(const Nodo& otro) const {
      return FuncionF_ < otro.FuncionF_;
    }
    
  private:
    std::pair<int, int> Coordenadas_; // Coordenadas del nodo en la matriz
    int Heuristico_; // Distancia estimada al objeto
    int Coste_; // Coste acumulado para llegar a este nodo
    int FuncionF_; // Funcion f
    std::pair<int,int> CoordenadasPadre_; // Puntero al nodo padre
};

// Constructor de la clase Nodo
Nodo::Nodo(std::pair<int, int> Coordenadas, int Coste, int Heuristico, int funcionF, std::pair<int,int> padre) {
  Coordenadas_ = Coordenadas;
  Coste_ = Coste;
  Heuristico_ = Heuristico;
  FuncionF_ = funcionF;
  CoordenadasPadre_ = padre;
}