#ifndef MAPA_H
#define MAPA_H

#include "../ciudad/ciudad.h"
#include <string>

using namespace std;

class Mapa {

private:
  std::string imagen; // ruta de la imagen de fondo a cargar
  Ciudad nodos[7];
  int matrizAdyacencia[7][7];

public:
  void ubicarNodos();
  void cargarImagen();
  void setMatriz();
  int distanciaNodos(int idOrigen, int idDestino);
  void setNodos();
};

#endif