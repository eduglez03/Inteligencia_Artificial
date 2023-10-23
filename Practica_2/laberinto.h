#include<iostream>
#include<vector>
#include<fstream>

class Laberinto {
  public:
    Laberinto(char*); // Constructor de la clase
    Laberinto() {}; // Constructor por defecto (no se usa)

    // Getters
    std::vector<std::vector<int>>& get_laberinto() { return laberinto_; }
    int get_numFilas() const { return numeroFilas_; }
    int get_numColumnas() const { return numeroColumnas_; }
    std::pair<int, int> get_posEntrada() const { return posEntrada_; }
    std::pair<int, int> get_posSalida() const { return posSalida_; }

    // Setters
    void set_laberinto(const std::vector<std::vector<int>>& laberinto) { laberinto_ = laberinto; }
    void set_posEntrada(int x, int y) { posEntrada_.first = x; posEntrada_.second = y; }
    void set_posSalida(int x, int y) { posSalida_.first = x; posSalida_.second = y; }
    void set_valor(int x, int y, int valor) { laberinto_[x][y] = valor; }

    void CambiarValor(int x, int y); // Acceder a una posicion concreta del laberinto
    void Imprimir();
    void ImprimirVisitados();
    void ImprimirLaberinto(const std::vector<Nodo>& camino);

  private:
    std::vector<std::vector<int>> laberinto_;
    int numeroFilas_;
    int numeroColumnas_;
    std::pair<int, int> posEntrada_; // Posicion entrada laberinto 
    std::pair<int, int> posSalida_; // Posicion salida laberinto 
    std::vector<std::vector<bool>> visitados_;
};

// Constructor de la clase
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


// Metodo que cambia un valor del laberinto
void Laberinto::CambiarValor(int x, int y) {
  laberinto_[x][y] = 3; // Cambiamos el valor de la posicion a '- ' 
}

void Laberinto::Imprimir() {
  for (int i = 0; i < numeroFilas_; i++) {
    for (int j = 0; j < numeroColumnas_; j++) {
      std::cout << laberinto_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Laberinto::ImprimirVisitados() {
  for (int i = 0; i < numeroFilas_; i++) {
    for (int j = 0; j < numeroColumnas_; j++) {
      std::cout << visitados_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}


// Función para imprimir el laberinto con información de los nodos de camino
void Laberinto::ImprimirLaberinto(const std::vector<Nodo>& camino) {
 for (int i = 0; i < this->get_numFilas(); ++i) {
    for (int j = 0; j < this->get_numColumnas(); ++j) {
      if (laberinto_[i][j] == 1) {
        std::cout << " X ";
      } else {
          auto it = std::find_if(camino.begin(), camino.end(),
            [i, j](const Nodo& nodo) {
            return nodo.get_coordenadas().first == i && nodo.get_coordenadas().second == j;
            });

          std::cout << (it != camino.end() ? " - " : " 0 ");
      }
    }
    std::cout << std::endl;
  }
}