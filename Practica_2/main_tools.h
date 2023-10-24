// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo main_tools.cc: Archivo que contiene las funciones del programa principal

#include<fstream>

#include "astar.h"

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
#define PATH_CHR  "*"
#define START_CHR "A"
#define END_CHR   "B"

/**
 * @brief Función que comprueba si los parametros de entrada son correctos
*/
void Usage(int argc, char* argv[]) {
  if(argc != 2) {
    std::cout << argv[0] << ": Falta el fichero con el laberinto" << std::endl;
    std::cout << "Pruebe " << argv[0] << " --help para más información" << std::endl;
    exit(EXIT_SUCCESS);
  }
}

/**
 * @brief Función que muestra la ayuda del programa

*/
void Help() {
  std::cout << "Este programa calcula y muestra el camino más corto para salir del laberinto" << std::endl;
  std::cout << "Ejecución: ./p02_astar_main <fichero_laberinto>" << std::endl;
  std::cout << "El fichero con el laberinto debe tener el siguiente formato:" << std::endl;
  std::cout << "  - La primera línea contiene el número de filas y columnas del laberinto separados por un espacio" << std::endl;
  std::cout << "  - Las siguientes líneas contienen el laberinto en sí, donde cada posición puede ser:" << std::endl;
  std::cout << "    - 0: pasillo" << std::endl;
  std::cout << "    - 1: pared" << std::endl;
  std::cout << "    - 3: inicio del laberinto" << std::endl;
  std::cout << "    - 4: salida del laberinto" << std::endl;
  exit(EXIT_SUCCESS);
}

/**
 * @brief Función que muestra el menu del programa

*/
void Menu(Laberinto& laberinto, int& heuristica, std::string fichero) {
  std::cout << "Porgrama que calcula y muestra el camino mas corto para salir del laberinto" << std::endl << std::endl;
  std::cout << "El laberinto se ha generado a partir del fichero: " << fichero << std::endl;
  std::cout << "Numero de Filas: " << laberinto.get_numFilas() << " Numero de columnas: " << laberinto.get_numColumnas() << std::endl;
  
  std::cout << "Posicion de entrada al laberinto: " << "(" << laberinto.get_posEntrada().first << ", " << laberinto.get_posEntrada().second << ")"<< std::endl;
  std::cout << "Posicion de salida al laberinto: " << "(" << laberinto.get_posSalida().first << ", " << laberinto.get_posSalida().second << ")" << std::endl << std::endl;
  
  std::cout << "¿Quiere cambiar las posiciones de entrada y salida? (s/n)" << std::endl;
  char respuesta;
  std::cin >> respuesta;

  if (respuesta == 's' || respuesta == 'S') {
    std::cout << "Introduzca la fila y la columna de la entrada" << std::endl;
    int fila1, columna1;
    std::cin >> fila1 >> columna1;
    laberinto.get_laberinto()[laberinto.get_posEntrada().first][laberinto.get_posEntrada().second] = 1;
    laberinto.set_posEntrada(fila1, columna1);
    laberinto.get_laberinto().at(laberinto.get_posEntrada().first).at(laberinto.get_posEntrada().second) = 3;

    std::cout << "Introduzca la fila y la columna de la salida" << std::endl;
    int fila2, columna2;
    std::cin >> fila2 >> columna2;
    laberinto.get_laberinto()[laberinto.get_posSalida().first][laberinto.get_posSalida().second] = 1;
    laberinto.set_posSalida(fila2, columna2);
    laberinto.get_laberinto().at(laberinto.get_posSalida().first).at(laberinto.get_posSalida().second) = 4;
  }

  std::cout << "Seleccione la Heurística que desea emplear: " << std::endl;
  std::cout << "1. Distancia Manhattan" << std::endl;
  std::cout << "2. Distancia Euclidea" << std::endl;
  std::cin >> heuristica;
}

/**
 * @brief Función que imprime el camino
*/
void ImprimirCamino(const Astar& astar, Laberinto laberinto, const std::vector<Nodo> generados) {
  std::cout << "Se ha encontrado el camino al final del laberinto" << std::endl;
  std::cout << "El camino es el siguiente: " << std::endl;
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

  std::cout << "El camino es el siguiente: " << std::endl;
  for (auto& nodo : camino) {
    if (nodo == camino.back()) {
      std::cout << "(" << nodo.get_coordenadas().first << ", " << nodo.get_coordenadas().second << ")";
    } else {
    std::cout << "(" << nodo.get_coordenadas().first << ", " << nodo.get_coordenadas().second << ") --> ";
    }
  }
  std::cout << std::endl;

  std::cout << "El coste del camino es: " << Final.get_coste() << std::endl;
  std::cout << "El número de nodos inspeccionados es: " << astar.get_nodosCerrados().size() << std::endl;
  std::cout << "El número de nodos generados es: " << generados.size() << std::endl;
}