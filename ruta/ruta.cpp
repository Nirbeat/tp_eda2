#include "ruta.h"

void Ruta::dibujarRuta(Coordenadas origen, Coordenadas destino) {
  // aca iria la logica del pintado de ruta, basicamente la línea
};

bool Ruta::cambiarEstadoRuta() {
  this->activa = !this->activa;
  return !this->activa;
};