#pragma once

#include<iostream>
#include<vector>
#include<set>

/**
 * @brief Declaracion de la clase Nodo
 * 
 */
class Nodo {
  public:
    Nodo(int); // Constructor de la clase
    Nodo() {} // Constructor por defecto
    Nodo(const Nodo& aux) { // Constructor Nodo
      identificador_= aux.identificador_;
      hijos_ = aux.hijos_;
      padre_ = aux.padre_;
      recorrido_ = aux.recorrido_;
    }

    int get_identificador(); // Getter identificador nodo
    void set_identificador(int); // Setter identificador nodo
    Nodo* get_padre(); // Getter padre del nodo
    void set_padre(Nodo*); // Setter padre del nodo
    void add_hijo(Nodo*); // Metodo para añadir un nuevo hijo a un nodo
    std::vector<Nodo*> get_hijos(); // Getter de vector de hijos de un nodo
    void set_hijos (std::vector<Nodo*> hijos) { hijos_= hijos; } // Setter vector hijos
    void set_recorrido (double recorrido) { recorrido_ = recorrido;} // Setter recorrido
    int nodos_totales_; // Nodos totales del grafo

    friend std::ostream& operator<<(std::ostream&, const Nodo&); // Sobrecarga operador extraccion
  
  private:
    int identificador_; // Identificador del nodo
    std::vector<Nodo*> hijos_; // Vector de adyacentes de un nodo
    Nodo* padre_; // Padre de un nodo
    double recorrido_; // Recorrido
    int profundidad_; // Profundidad
};