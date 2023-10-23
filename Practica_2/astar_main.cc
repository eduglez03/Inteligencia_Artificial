// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo p02_astar_main.cc: Archivo principal del programa

#include<iostream>

#include "main_tools.h"

// Funcion principal del programa
int main (int argc, char* argv[]) {
  // Comprobamos que la ejecucion y los parametros sean correctos
  if (std::string(argv[1]) == "--help") {
    Help();
    exit(EXIT_SUCCESS);
  } else {
    Usage(argc, argv); 
  }

  // Generamos el laberinto
  Laberinto laberinto(argv[1]);
  int heuristica_seleccionada{0};

  // Mostramos el menu
  Menu(laberinto, heuristica_seleccionada, std::string(argv[1]));

  // Generamos el objeto Astar
  Astar astar;
  std::vector<Nodo> generados;
  
  // Comprobamos si se ha encontrado el camino y lo imprimimos
  if (astar.ObtenerCamino(laberinto, heuristica_seleccionada, generados) == true) {
    ImprimirCamino(astar, laberinto, generados);
  } else {
    std::cout << "No se ha encontrado el camino al final del laberinto" << std::endl;
  }
  
  return 0;
}