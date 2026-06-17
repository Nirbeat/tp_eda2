#ifndef CIUDAD_H
#define CIUDAD_H

#include "../structs.h"

class Ciudad {
private:
  std::string nombre;
  struct Coordenadas coordenadas;
  int id;
  bool activa;

public:
  Ciudad();
	Ciudad(int id, const std::string& nombre, Coordenadas coordenadas);
  std::string obtenerNombre();
  struct Coordenadas obtenerCoordenadas();
  int obtenerId();
  bool obtenerEstado();
  void cambiarEstado();
};

#endif