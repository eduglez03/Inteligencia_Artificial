// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo nodo.cc: En este archivo se implementan las funciones de la clase Nodo

#include "nodo.h"

/**
 * @brief Constructor de la clase Nodo
*/
Nodo::Nodo(std::pair<int, int> Coordenadas, int Coste, int Heuristico, int funcionF, std::pair<int,int> padre) {
  Coordenadas_ = Coordenadas;
  Coste_ = Coste;
  Heuristico_ = Heuristico;
  FuncionF_ = funcionF;
  Padre_ = padre;
}