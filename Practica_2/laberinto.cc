// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo laberinto.cc: En este archivo se implementan las funciones de la clase Laberinto

#include "laberinto.h"

/**
 * @brief Constructor de la clase Laberinto
*/
Laberinto::Laberinto(char* fichero_entrada) {
  int elemento_leido{0};

  std::ifstream fichero(fichero_entrada);  // Abrimos el fichero de entrada
  fichero >> numeroFilas_;  // Almacenamos el numero de filas de la matriz
  fichero >> numeroColumnas_; // Almacenamos el numero de columnas de la matriz

  laberinto_.resize(numeroFilas_ + 1, std::vector<int>(numeroColumnas_ + 1, 0)); // Resize de la matriz con las filas y columnas

  for (int i = 0; i < numeroFilas_; i++) {
    for (int j = 0; j < numeroColumnas_; j++) {
      fichero >> elemento_leido;
      laberinto_[i][j] = elemento_leido;
      if (elemento_leido == 3) {
        posEntrada_.first = i;
        posEntrada_.second = j;
      }
      if (elemento_leido == 4) {
        posSalida_.first = i;
        posSalida_.second = j;
      }
    }
  }
}