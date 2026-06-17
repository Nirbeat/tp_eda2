#ifndef RUTA_H
#define RUTA_H

#include <mapa.h>
#include <structs.h>

class Ruta {
public:
	Ruta();
	struct ResultadoRuta encontrarRuta(int** matriz, int cantidadCiudad, int idOrigen, int idDestino);
};

#endif
