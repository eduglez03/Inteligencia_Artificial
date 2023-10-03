#include "nodo.h"

/**
 * @brief Construct a new Nodo:: Nodo object
 * 
 * @param identificador 
 */
Nodo::Nodo(int identificador) {
  identificador_ = identificador;
}

/**
 * @brief Getter identificador nodo
 * 
 * @return int 
 */
int Nodo::get_identificador() {
  return identificador_;
}

/**
 * @brief Setter identificador nodo
 * 
 * @param identificador 
 */
void Nodo::set_identificador(int identificador) {
  identificador_ = identificador;
}

/**
 * @brief Getter padre del nodo
 * 
 * @return Nodo* 
 */
Nodo* Nodo::get_padre() {
  return padre_;
}

/**
 * @brief Setter padre del nodo
 * 
 * @param padre 
 */
void Nodo::set_padre(Nodo* padre) {
  padre_ = padre;
}

/**
 * @brief Metodo que añade un nuevo nodo hijo del nodo actual
 * 
 * @param hijo 
 */
void Nodo::add_hijo(Nodo* hijo) {
  hijos_.push_back(hijo);
  hijo->set_padre(this);
}

/**
 * @brief Getter de vector de hijos de un nodo
 * 
 * @return std::vector<Nodo*> 
 */
std::vector<Nodo*> Nodo::get_hijos() {
  return hijos_;
}

/**
 * @brief Sobrecarga operador extraccion
 * 
 * @param output 
 * @param nodo 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& output, const Nodo& nodo) {
  output << "Nodo(" << nodo.identificador_ << ")";
  return output;
}



