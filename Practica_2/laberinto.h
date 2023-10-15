#include<iostream>
#include<vector>
#include<fstream>

class Laberinto {
  public:
    Laberinto(char*); // Constructor de la clase

    // Getters
    std::vector<std::vector<int>> get_laberinto() {return laberinto_;}
    int get_numFilas() {return numeroFilas_;}
    int get_numColumnas() {return numeroColumnas_;}
    std::pair<int, int> get_posEntrada() {return posEntrada_;}
    std::pair<int, int> get_posSalida() {return posSalida_;}

  private:
    std::vector<std::vector<int>> laberinto_;
    int numeroFilas_;
    int numeroColumnas_;
    std::pair<int, int> posEntrada_; // Posicion entrada laberinto 
    std::pair<int, int> posSalida_; // Posicion salida laberinto 
};

// Constructor de la clase
Laberinto::Laberinto(char* fichero_entrada) {
  int elemento_leido{0};

  std::ifstream fichero(fichero_entrada);  // Abrimos el fichero de entrada
  fichero >> numeroFilas_;  // Almacenamos el numero de filas de la matriz
  fichero >> numeroColumnas_; // Almacenamos el numero de columnas de la matriz

  laberinto_.resize(numeroFilas_ + 1 * numeroColumnas_ + 1); // Resize de la matriz con las filas y columnas

  for (int i = 0; i < numeroFilas_; i++) {
    for (int j = 0; j < numeroColumnas_; j++) {
      fichero >> elemento_leido;
      laberinto_[i,j].push_back(elemento_leido);
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