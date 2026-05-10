#ifndef RUTA_H
#define RUTA_H

#include "../structs.h"
class Ruta {
private:
  bool activa;

public:
  Ruta() : activa(true) {}

  void dibujarRuta(Coordenadas origen, Coordenadas destino);
  bool cambiarEstadoRuta();
  bool estaActiva() const { return activa; };
};

#endif