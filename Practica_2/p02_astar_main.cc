#include<fstream>

#include "p02_aestar.h"


// indica pasillo
#define PASS_ID  0
// indica pared
#define WALL_ID  1
// indica camino de salida
#define PATH_ID  2
// indica inicio del laberinto
#define START_ID 8
// indica la salida del laberinto
#define END_ID   9

// caracteres usados para mostrar el laberinto por pantalla
#define WALL_CHR  "█"
#define PASS_CHR  " "
#define PATH_CHR  "·"
#define START_CHR "A"
#define END_CHR   "B"


void Usage(int argc, char* argv[]) {

}



int main (int argc, char* argv[]) {
  // Hacer comprobaciones ficheros entrada

  // Comprobamos que la ejecucion y los parametros sean correctos
  Usage(argc, argv); 

  // Generamos el laberinto
  Laberinto laberinto(argv[1]);


  std::cout << "Porgrama que calcula y muestra el camino mas corto para salir del laberinto" << std::endl << std::endl;
  std::cout << "El laberinto se ha generado a partir del fichero: " << argv[1] << std::endl;
  std::cout << "Numero de Filas: " << laberinto.get_numFilas() << " Numero de columnas: " << laberinto.get_numColumnas() << std::endl;
  
  std::cout << "Posicion de entrada al laberinto: " << "(" << laberinto.get_posEntrada().first << ", " << laberinto.get_posEntrada().second << ")"<< std::endl;
  std::cout << "Posicion de salida al laberinto: " << "(" << laberinto.get_posSalida().first << ", " << laberinto.get_posSalida().second << ")" << std::endl << std::endl;
  
  
/*
  std::cout << "¿Quiere cambiar las posiciones de entrada y salida? (s/n)" << std::endl;
  char respuesta;
  std::cin >> respuesta;

  if (respuesta == 's' || respuesta == 'S') {
    std::cout << "Introduzca la fila y la columna de la entrada" << std::endl;
    int fila, columna;
    std::cin >> fila >> columna;
    laberinto.get_laberinto().at(laberinto.get_posEntrada().first).at(laberinto.get_posEntrada().second) = 1;
    laberinto.Imprimir();
    laberinto.set_posEntrada(fila, columna);
    laberinto.get_laberinto()[laberinto.get_posEntrada().first][laberinto.get_posEntrada().second] = 3;

    std::cout << "Introduzca la fila y la columna de la salida" << std::endl;
    std::cin >> fila >> columna;
    laberinto.get_laberinto()[laberinto.get_posSalida().first][laberinto.get_posSalida().second] = 1;
    laberinto.set_posSalida(fila, columna);
    laberinto.get_laberinto()[laberinto.get_posSalida().first][laberinto.get_posSalida().second] = 4;

    std::cout << "El laberinto generado es: " << std::endl;
    laberinto.Imprimir();
  }
*/

  std::cout << "Seleccione la Heurística que desea emplear: " << std::endl;
  std::cout << "1. Distancia Manhattan" << std::endl;
  std::cout << "2. Distancia Euclidea" << std::endl;
  int heuristica;
  std::cin >> heuristica;

  // Buscamos la salida al laberinto
  Astar astar;
  astar.set_laberinto(laberinto);
  
  // Comprobamos si se ha encontrado el camino y lo imprimimos
  if (astar.ObtenerCamino(laberinto.get_posEntrada(), laberinto.get_posSalida(), heuristica) == true) {
    std::vector<Nodo> camino;

    Nodo revisado = astar.get_nodosCerrados().back();
    Nodo Final = astar.get_nodosCerrados().back();
    astar.get_nodosCerrados().pop_back();

    for(int i = astar.get_nodosCerrados().size(); i > 0; i--) {
      for (auto& nodo : astar.get_nodosCerrados()) {
        if (nodo.get_coordenadas() == revisado.get_Padre()) {
          revisado = nodo;
          camino.push_back(revisado);
        }
      }
      
    }
    std::reverse(camino.begin(), camino.end());
    camino.push_back(Final); 

    for (int i = 0; i < camino.size(); i++) {
      std::cout << "(" << camino[i].get_coordenadas().first << ", " << camino[i].get_coordenadas().second << ")" << std::endl;
    }


    for(int i = 0; i < laberinto.get_numFilas(); i++) {
      for(int j = 0; j < laberinto.get_numColumnas(); j++) {
        if (laberinto.get_laberinto()[i][j] == WALL_ID) {
          std::cout << WALL_CHR << " ";
        } else {
          bool encontrado = false;
          for(auto& nodo : camino) {
            if (nodo.get_coordenadas().first == i && nodo.get_coordenadas().second == j) {
              std::cout << PATH_CHR << " ";
              encontrado = true;
            }
          }
          if (!encontrado) {
            std::cout << PASS_CHR << " ";
          }
        }
      }
      std::cout << std::endl;
    }

  } else 
    std::cout << "No se ha encontrado el camino al final del laberinto" << std::endl;

  return 0;
}