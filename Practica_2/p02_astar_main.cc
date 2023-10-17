#include<iostream>
#include<fstream>
#include<vector>

#include "p02_aestar.h"

void Usage(int argc, char* argv[]) {

}



int main (int argc, char* argv[]) {
  // Hacer comprobaciones ficheros entrada

  // Comprobamos que la ejecucion y los parametros sean correctos
  Usage(argc, argv); 

  // Generamos el laberinto
  Laberinto laberinto(argv[1]);

  // Buscamos la salida al laberinto
  Astar astar;
  astar.set_laberinto(laberinto.get_laberinto());
  

  if (astar.obtenerCamino(laberinto.get_posEntrada(), laberinto.get_posSalida())) {
    // Imprimir resultado
    for(int i = 0; i < laberinto.get_numFilas(); i++) {
      for(int j = 0; j < laberinto.get_numColumnas(); j++) {
        for(auto nodo : astar.get_nodosCerrados()) {
          if(nodo.get_coordenadas().first == i && nodo.get_coordenadas().second == j) {
            laberinto.CambiarValor(i, j);
          }
        }
      }
    }
  } else {
    std::cout << "No se ha encontrado el camino al final del laberinto" << std::endl;
  }

  return 0;
}