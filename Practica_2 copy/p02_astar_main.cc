#include<fstream>

#include "p02_aestar.h"

void Usage(int argc, char* argv[]) {

}



int main (int argc, char* argv[]) {
  // Hacer comprobaciones ficheros entrada

  // Comprobamos que la ejecucion y los parametros sean correctos
  Usage(argc, argv); 

  // Generamos el laberinto
  Laberinto laberinto(argv[1]);
  std::cout << laberinto.get_posEntrada().first << " " << laberinto.get_posEntrada().second << std::endl;
  std::cout << laberinto.get_posSalida().first << " " << laberinto.get_posSalida().second << std::endl;
  //laberinto.Imprimir();

  //std::cout << std::endl;

  //laberinto.ImprimirVisitados();

  // Buscamos la salida al laberinto
  Astar astar;
  astar.set_laberinto(laberinto);
  

  if (astar.obtenerCamino(laberinto.get_posEntrada(), laberinto.get_posSalida()) == true) {
    for (auto elemento : astar.get_nodosCerrados()) {
      std::cout << "(" << elemento->get_coordenadas().first << "," << elemento->get_coordenadas().second << ")   " <<  "   Heuristico: " << elemento->get_heuristico() << "   Coste: " << elemento->get_coste() << "   Funcion F: " << elemento->get_funcionF() << std::endl;
    }
    /*
    for (int i = 0; i < laberinto.get_numFilas(); i++) {
      for (int j = 0; j < laberinto.get_numColumnas(); j++) {
        for (auto& elemento : astar.get_nodosCerrados()) {
          if ((i == elemento.get_coordenadas().first) && (j = elemento.get_coordenadas().second)) {
            laberinto.CambiarValor(i, j);
          }
        }
      }
    }

    for (int i = 0; i < laberinto.get_numFilas(); i++) {
      for (int j = 0; j < laberinto.get_numColumnas(); j++) {
        std::cout << laberinto.get_laberinto().at(i).at(j) << " ";
      }
      std::cout << std::endl;
    }
    */

  } else 
    std::cout << "No se ha encontrado el camino al final del laberinto" << std::endl;

  return 0;
}