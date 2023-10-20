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
  laberinto.Imprimir();

  std::cout << std::endl;



  // Buscamos la salida al laberinto
  Astar astar;
  astar.set_laberinto(laberinto);
  
  // Comprobamos si se ha encontrado el camino y lo imprimimos
  if (astar.ObtenerCamino(laberinto.get_posEntrada(), laberinto.get_posSalida()) == true) {
    std::vector<Nodo> camino;

    Nodo revisado = astar.get_nodosCerrados().back();
    Nodo Final = astar.get_nodosCerrados().back();
    astar.get_nodosCerrados().pop_back();

    for(int i = astar.get_nodosCerrados().size(); i > 0; i--) {
      for (auto& nodo : astar.get_nodosCerrados()) {
        if (nodo.get_coordenadas() == revisado.get_Coordenadaspadre()) {
          revisado = nodo;
          camino.push_back(revisado);
        }
      }
      
    }
    std::reverse(camino.begin(), camino.end());
    camino.push_back(Final); 

    for(auto& nodos : camino) {
      std::cout << "(" << nodos.get_coordenadas().first << "," << nodos.get_coordenadas().second << ")" << std::endl;
    
    }

  } else 
    std::cout << "No se ha encontrado el camino al final del laberinto" << std::endl;

  return 0;
}