// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo p02_astar.cc: Archivo que contiene la clase Astar

#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<utility>
#include <algorithm> // Para std::min_element
#include <cmath> // Para std::sqrt
#include <cstdlib> // Para la función rand y srand
#include <ctime>   // Para la función time

#include "nodo.h"
#include "laberinto.h"


// Enumerar las direcciones posibles:
enum direciones {A, AD, D, DB, B, BI, I, IA};

//Definimos vectores de desplazamientos para cada direccion;
//                            A    AB    D    DB    B    BI    I    IA
const short movimiento_i[] = {-1, -1,   0,    1,    1,   1,    0,   -1};
const short movimiento_j[] = {0,   1,   1,    1,    0,   -1,  -1,   -1};

// Clase Astar
class Astar {
  public:
    Astar() {}; // Constructor por defecto

    // Getters
    std::vector<Nodo> get_nodosCerrados() const {return nodosCerrados_;} // Getter nodos cerrados
    std::vector<Nodo> get_nodosAbiertos() const { return nodosAbiertos_; }  // Getter nodos abiertos 

    // Funcion
    int Manhattan(const std::pair<int, int>& origen, const std::pair<int, int>& destino); // Funcion Manhattan
    int Euclidea(const std::pair<int, int>& origen, const std::pair<int, int>& destino);  // Funcion Euclidea
    int CalularF(int heuristico, int coste); // Funcion que calcula la funcion F
    Nodo MenorCoste(); // Funcion que obtiene el nodo de menor coste de la lista de nodos abiertos
    bool ObtenerCamino(Laberinto& laberinto, int heuristica, std::vector<Nodo>& generados); // Funcion que obtiene el camino
    bool ComprobarAbiertos(const Nodo& nodo); // Funcion que comprueba si el nodo ya esta en la lista de nodos abiertos
    bool ComprobarCerrados(const Nodo& nodo);  // Funcion que comprueba si el nodo ya esta en la lista de nodos cerrados
    bool ActualizarCoste(const Nodo& nodo);  // Funcion que actualiza la lista de nodos abiertos si el nodo que estamos analizando tiene un coste menor

  private:
    std::vector<Nodo> nodosCerrados_; // Lista de nodos cerrados
    std::vector<Nodo> nodosAbiertos_; // Cola de nodos abiertos
    const int costeHV_ = 5; // Valor del coste horizontal y vertical
    const int costeDiagonal_ = 7; // Valor coste diagonal
};