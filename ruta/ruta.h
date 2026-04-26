#ifndef RUTA_H
#define RUTA_H

#include "../structs.h"
class Ruta {
  // ESTE BOOL QUEDA HARDCODEADO PORQUE POR DEFECTO LA RUTA, CUANDO SE CREE,
  // DEBERIA DIBUJARSE A MENOS QUE EL USUSARIO INDIQUE POSTERIORMENTE
  // QUE ESTÁ CORTADA
  bool estado = true;
  void dibujarRuta(Coordenadas origen, Coordenadas destino);
  bool cambiarEstadoRuta(); // permite switchear el estado a disponbible/no
                            // disponible, pero hay que ver si tiene sentido
};

#endif