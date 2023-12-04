// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo nodo.h: En este archivo se definen la clase Nodo

#include<iostream>
#include <utility> // Necesario para std::pair

// Clase Nodo
class Nodo {
  public:
    Nodo(std::pair<int, int>, int, int, int, std::pair<int,int>); // Constructor de la clase Nodo
    Nodo() {} // Constructor por defecto
    ~Nodo() {} // Destructor de la clase Nodo

    void set_coordenadas(std::pair<int, int> coordenadas) { Coordenadas_ = coordenadas; } // Setter coordenadas nodo en la matriz
    void set_heuristico(int heuristico) { Heuristico_ = heuristico; } // Setter heuristico
    void set_coste(int coste) { Coste_ = coste; } // Setter coste
    void set_padre(std::pair<int,int> padre) { Padre_ = padre; } // Setter padre
    void set_funcionF(int funcionF) { FuncionF_ = funcionF; } // Setter funcion f

    std::pair<int,int> get_coordenadas() const { return Coordenadas_; } // Getter coordenadas nodo
    int get_heuristico() const { return Heuristico_; } // Getter heuristico
    int get_coste() const { return Coste_; } // Getter coste
    int get_funcionF() const { return FuncionF_; } // Getter funcion f
    std::pair<int,int> get_Padre() const { return Padre_; } // Getter padre

    // Sobrecarga del operador >
    bool operator>(const Nodo& otro) const {
      return FuncionF_ > otro.FuncionF_;
    }

    // Sobrecarga del operador <
    bool operator<(const Nodo& otro) const {
      return FuncionF_ < otro.FuncionF_;
    }
    
    // Sobrecarga del operador de igualdad
    bool operator==(const Nodo& otro) const {
      return Coordenadas_ == otro.Coordenadas_;
    }

  private:
    std::pair<int, int> Coordenadas_; // Coordenadas del nodo en la matriz
    int Heuristico_; // Distancia estimada al objeto
    int Coste_; // Coste acumulado para llegar a este nodo
    int FuncionF_; // Funcion f
    std::pair<int,int> Padre_; // Coordenadas del nodo padre
};