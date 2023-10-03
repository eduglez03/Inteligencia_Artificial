#include "grafo.h"


/**
 * @brief Resize vector nodos
 * 
 * @param valor 
 */
void Grafo::vectorResize(int valor) { nodosGrafo_.resize(valor); }

/**
 * @brief Getter nodo del grafo
 * 
 * @param pos 
 * @return Nodo* 
 */
Nodo* Grafo::get_nodo(int pos) { return nodosGrafo_.at(pos); }

/**
 * @brief Metodo que comprueba si un nodo es padre de otro
 * 
 * @param primero 
 * @param segundo 
 * @return true 
 * @return false 
 */
bool Grafo::EsPadre(Nodo* primero, Nodo* segundo) {
  if (primero->get_padre() == nullptr) {
    return false;
  } else if (primero == segundo) {
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Metodo que crea un nuevo nodo en el BFS y en el DFS
 * 
 * @param segundo 
 * @return Nodo* 
 */
Nodo* Grafo::CrearNodo(Nodo* segundo) {
  Nodo* nuevo = new Nodo;
  nuevo->set_padre(segundo);
  nuevo->set_identificador(segundo->get_identificador());
  return nuevo;
}

/**
 * @brief BFS
 * 
 * @param inicial 
 * @param total_nodos 
 * @param coste_final 
 * @param arbol_resultado 
 * @return true 
 * @return false 
 */
bool Grafo::bfs(Nodo* inicial, Nodo* final, int total_nodos, double coste_final, Arbol& arbol_resultado) {
  int aristas = 0; 
  std::vector<int> visitados;
  std::vector<Nodo*> generados;
  std::vector<int> camino;

  // Mantener un mapa de padres para reconstruir el camino
  std::map<int, Nodo*> padres;

  inicial->set_padre(nullptr);

  std::queue<Nodo*> pila;
  pila.push(inicial);

  while (!pila.empty()) {
    Nodo* actual = pila.front();
    int padre_actual = actual->get_identificador();
    pila.pop();

    if (actual->get_identificador() == final->get_identificador()) {
      while (actual != nullptr) {
        camino.push_back(actual->get_identificador());
        actual = actual->get_padre();
      }
      
      std::reverse(camino.begin(), camino.end());
      
      arbol_resultado.set_costeTotal(coste_final);
      arbol_resultado.set_nodoFinal(final);
      arbol_resultado.set_nodoInicial(inicial);
      arbol_resultado.set_vectorGenerados(generados);
      arbol_resultado.set_vectorVisitados(visitados);
      arbol_resultado.set_Camino(camino);
      return true;
    }

    visitados.push_back(actual->get_identificador());

    for (auto i : actual->get_hijos()) {
      Nodo* ptr = actual;
      bool rama = false;
      while(ptr != nullptr) {
        if (ptr->get_identificador() == i->get_identificador() ) {rama = true;}
        ptr = ptr->get_padre();
      }
      if (rama == false) {
        generados.push_back(i);
        int padre_actual = actual->get_identificador();
        bool encontrado = false;
        Nodo* aux = new Nodo (i->get_identificador());
        aux->set_padre(actual);
        aux->set_hijos(i->get_hijos());
        for (int j = 0; j < visitados.size(); ++j) {
          if (visitados[j] == i->get_identificador()) {
            encontrado = true;
            break;
          }
        }
        if (encontrado == false) {
          pila.push(aux);
          // Registrar el padre de este nodo
          padres[i->get_identificador()] = actual;
        }
      }
    }
    std::queue<Nodo*> copia = pila;
    while (!copia.empty()) {
      copia.pop();
    }
  }

  return false;
}

/**
 * @brief DFS
 * 
 * @param inicial 
 * @param total_nodos 
 * @param coste_final 
 * @param arbol_resultado 
 * @return true 
 * @return false 
 */
bool Grafo::dfs(Nodo* inicial, Nodo* final, int total_nodos, double coste_final, Arbol& arbol_resultado) {
  int aristas = 0; 
  std::vector<int> visitados;
  std::vector<Nodo*> generados;
  std::vector<int> camino;

  // Mantener un mapa de padres para reconstruir el camino
  std::map<int, Nodo*> padres;

  inicial->set_padre(nullptr);

  std::stack<Nodo*> pila;
  pila.push(inicial);

  while (!pila.empty()) {
    Nodo* actual = pila.top();
    int padre_actual = actual->get_identificador();
    pila.pop();

    if (actual->get_identificador() == final->get_identificador()) {
      while (actual != nullptr) {
        camino.push_back(actual->get_identificador());
        actual = actual->get_padre();
      }
      
      std::reverse(camino.begin(), camino.end());
      
      arbol_resultado.set_costeTotal(coste_final);
      arbol_resultado.set_nodoFinal(final);
      arbol_resultado.set_nodoInicial(inicial);
      arbol_resultado.set_vectorGenerados(generados);
      arbol_resultado.set_vectorVisitados(visitados);
      arbol_resultado.set_Camino(camino);
      return true;
    }

    visitados.push_back(actual->get_identificador());

    for (auto i : actual->get_hijos()) {
      Nodo* ptr = actual;
      bool rama = false;
      while(ptr != nullptr) {
        if (ptr->get_identificador() == i->get_identificador() ) {rama = true;}
        ptr = ptr->get_padre();
      }
      if (rama == false) {
        generados.push_back(i);
        int padre_actual = actual->get_identificador();
        bool encontrado = false;
        Nodo* aux = new Nodo (i->get_identificador());
        aux->set_padre(actual);
        aux->set_hijos(i->get_hijos());
        for (int j = 0; j < visitados.size(); ++j) {
          if (visitados[j] == i->get_identificador()) {
            encontrado = true;
            break;
          }
        }
        if (encontrado == false) {
          pila.push(aux);
          // Registrar el padre de este nodo
          padres[i->get_identificador()] = actual;
        }
      }
    }
    std::stack<Nodo*> copia = pila;
    while (!copia.empty()) {
      copia.pop();
    }
  }

  return false;
}