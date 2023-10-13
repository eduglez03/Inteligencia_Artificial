#include<iostream>
#include<fstream>
#include<vector>

#include "p02_aestar.h"

void Usage(int argc, char* argv[]) {

}



int main (int argc, char* argv[]) {
  // Hacer comprobaciones ficheros entrada

  Usage(argc, argv); // Función para comprobar si los parametros introducidos por el usuario son correctos

  int filas{0}; // Variable que almacena el numero de filas de la matriz
  int columnas{0}; // Variables que almacena el numero de columnas de la matriz
  int elemento_leido{0};
  std::vector<std::vector<int>> matriz; // Matriz 

  std::ifstream archivo_entrada(argv[1]);  // Abrimos el fichero de entrada
  archivo_entrada >> filas;  // Almacenamos el numero de filas de la matriz
  archivo_entrada >> columnas; // Almacenamos el numero de columnas de la matriz
  std::pair<int, int> entrada; // Posicion entrada laberinto 
  std::pair<int, int> salida; // Posicion salida laberinto 

  matriz.resize(filas + 1 * columnas + 1); // Resize de la matriz con las filas y columnas

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      archivo_entrada >> elemento_leido;
      matriz[i,j].push_back(elemento_leido);
      if (elemento_leido == 3) {
        entrada.first = i;
        entrada.second = j;
      }
      if (elemento_leido == 4) {
        salida.first = i;
        salida.second = j;
      }
    }
  }

  std::vector<Nodo> camino;
  Astar objetoAstar;
  objetoAstar.set_Matriz(matriz);

  camino = objetoAstar.astar();
  objetoAstar.get_NodosAbiertos();
  objetoAstar.get_NodosCerrados();

  return 0;
}