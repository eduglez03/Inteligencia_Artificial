#include<iostream>
#include<fstream>
#include<vector>

#include "p02_aestar.h"
#include "laberinto.h"

void Usage(int argc, char* argv[]) {

}



int main (int argc, char* argv[]) {
  // Hacer comprobaciones ficheros entrada

  // Comprobamos que la ejecucion y los parametros sean correctos
  Usage(argc, argv); 

  // Generamos el laberinto
  Laberinto laberinto(argv[1]);

  // Buscamos la salida al laberinto
  Astar astar(laberinto);
  astar.buscarCamino(laberinto.get_posEntrada(), laberinto.get_posSalida());

  return 0;
}