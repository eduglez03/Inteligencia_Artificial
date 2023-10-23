// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnologíıa
// Grado en Ingeniería Informática
// Asignatura: Inteligencia Artificial
// Curso: 3º
// Práctica 3: Búsqueda en espacio de estados
// Autor: Eduardo González Gutiérrez
// Correo: alu0101461588@ull.edu.es
// Fecha: 25/10/2023
// Archivo laberinto.h: En este archivo se definen la clase Laberinto

#include<iostream>
#include<vector>
#include<fstream>


// Clase Laberinto
class Laberinto {
  public:
    Laberinto(char*); // Constructor de la clase
    Laberinto() {}; // Constructor por defecto (no se usa)

    // Getters
    std::vector<std::vector<int>>& get_laberinto() { return laberinto_; } // Getter laberinto
    int get_numFilas() const { return numeroFilas_; } // Getter numero de filas
    int get_numColumnas() const { return numeroColumnas_; } // Getter numero de columnas
    std::pair<int, int> get_posEntrada() const { return posEntrada_; } // Getter posicion entrada
    std::pair<int, int> get_posSalida() const { return posSalida_; } // Getter posicion salida

    // Setters
    void set_laberinto(const std::vector<std::vector<int>>& laberinto) { laberinto_ = laberinto; } // Setter laberinto
    void set_posEntrada(int x, int y) { posEntrada_.first = x; posEntrada_.second = y; } // Setter posicion entrada
    void set_posSalida(int x, int y) { posSalida_.first = x; posSalida_.second = y; } // Setter posicion salida

  private:
    std::vector<std::vector<int>> laberinto_; // Matriz que representa el laberinto
    int numeroFilas_; // Numero de filas del laberinto
    int numeroColumnas_; // Numero de columnas del laberinto
    std::pair<int, int> posEntrada_; // Posicion entrada laberinto 
    std::pair<int, int> posSalida_; // Posicion salida laberinto 
    std::vector<std::vector<bool>> visitados_;
};