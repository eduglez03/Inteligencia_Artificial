#include "arbol.h"

// Setters
void Arbol::set_nodoInicial(Nodo* nodoInicial) {
  nodoInicial_ = nodoInicial;
}

void Arbol::set_nodoFinal(Nodo* nodoFinal) {
  nodoFinal_ = nodoFinal;
}

void Arbol::set_totalNodos(int totalNodos) {
  totalNodos_ = totalNodos;
}

void Arbol::set_costeTotal(double costeFinal) {
  costeFinal_ = costeFinal;
}

void Arbol::set_vectorGenerados(std::vector<Nodo*> vectorGenerados) {
  vectorGenerados_ = vectorGenerados;
}

void Arbol::set_vectorVisitados(std::vector<int> vectorVisitados) {
  vectorVisitados_ = vectorVisitados;
}

void Arbol::set_Camino(std::vector<int> Camino) {
  Camino_ = Camino;
}

// Getters
Nodo* Arbol::get_nodoInicial() {
  return nodoInicial_;
}

Nodo* Arbol::get_nodoFinal() {
  return nodoFinal_;
}

int Arbol::get_totalNodos() {
  return totalNodos_;
}

double Arbol::get_costeTotal() {
  return costeFinal_;
}

std::vector<Nodo*> Arbol::get_vectorGenerados() {
  return vectorGenerados_;
}

std::vector<int> Arbol::get_vectorVisitados() {
  return vectorVisitados_;
}

std::vector<int> Arbol::get_Camino() {
  return Camino_;
}




void Arbol::imprimirResultado() {
  int aristas{0};

  std::cout << "   Número de nodos = " << this->get_totalNodos() << std::endl;
  std::cout << "   Nodo inicial -> " << this->get_nodoInicial()->get_identificador() << std::endl;
  std::cout << "   Nodo final -> " << this->get_nodoFinal()->get_identificador() << std::endl;
  std::cout << "   Coste -> " << this->get_costeTotal() << std::endl;

  std::cout << "   Generados: ";
  for (auto i : this->get_vectorGenerados()) {
    std::cout << i->get_identificador() << ", ";
  }
  std::cout << std::endl;
  
  std::cout << "   Visitados: ";
  for (auto i : this->get_vectorVisitados()) {
    std::cout << i << ", ";
    aristas++;
  }
  std::cout << std::endl;
  
  std::cout << "   Camino: ";
  for (auto i : this->get_Camino()) {
    std::cout << "[" << i << "]" << " <- ";
  }
  std::cout << std::endl;
  
  std::cout << "   Número aristas totales -> " << aristas << std::endl;
  std::cout << std::endl;
}