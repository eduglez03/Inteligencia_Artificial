#pragma once

#include "nodo.h"

/**
 * @brief Declaracion clase arbol
 * 
 */
class Arbol {
  public:
    Arbol() {} // Constructor por defecto
    Arbol(Nodo*, Nodo*, int, double){} // Constructor de la clase 

    // Setters
    void set_nodoInicial(Nodo*);
    void set_nodoFinal(Nodo*);
    void set_totalNodos(int);
    void set_costeTotal(double);
    void set_vectorGenerados(std::vector<Nodo*>);
    void set_vectorVisitados(std::vector<int>);
    void set_Camino(std::vector<int>);

    // Getters
    Nodo* get_nodoInicial();
    Nodo* get_nodoFinal();
    int get_totalNodos();
    double get_costeTotal();
    std::vector<Nodo*> get_vectorGenerados();
    std::vector<int> get_vectorVisitados();
    std::vector<int> get_Camino();

    void imprimirResultado();

  private:
    Nodo* nodoInicial_;
    Nodo* nodoFinal_;
    int totalNodos_;
    double costeFinal_;
    std::vector<Nodo*> vectorGenerados_;
    std::vector<int> vectorVisitados_;
    std::vector<int> Camino_;
};