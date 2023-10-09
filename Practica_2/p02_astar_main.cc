#include<iostream>
#include<fstream>
#include<vector>



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

  matriz.resize(filas + 1 * columnas + 1); // Resize de la matriz con las filas y columnas


  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      archivo_entrada >> elemento_leido;
      matriz[i,j].push_back(elemento_leido);
    }
  }














  /*
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      std::cout << matriz.at(j).at(i) << "  ";
    }
    std::cout << std::endl;
  }
  */



  return 0;
}