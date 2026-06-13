#ifndef CIUDAD_H
#define CIUDAD_H

#include "../structs.h"

class Ciudad {
private:
  char nombre[30];
  struct Coordenadas coordenadas;
  int id;
  bool activa;

public:
  Ciudad();
  Ciudad(int id, const char *nombre, struct Coordenadas coordenadas);
  char *obtenerNombre();
  struct Coordenadas obtenerCoordenadas();
  int obtenerId();
  bool obtenerEstado();
  void cambiarEstado();
};

#endif