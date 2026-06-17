#include "Logistica.h"

#include <cmath>
#include <limits>
#include <sstream>

SistemaLogistico::SistemaLogistico()
	: cantidadHistorial(0) {
	inicializarCiudades();
	inicializarRutas();
}

void SistemaLogistico::inicializarCiudades() {
//este recibe los datos de la carga de ciudades del archivo, recorre el
//array y por cada una de las ciudades pinta en el mapa la ubicacion


//	ciudades[0] = CiudadLogistica{0, "Calafate", -72.3, -50.3, 0.34, 0.77, true, false};
//	ciudades[1] = CiudadLogistica{1, "Gobernador Gregores", -70.2, -48.8, 0.50, 0.52, true, false};
//	ciudades[2] = CiudadLogistica{2, "Puerto San Julian", -67.7, -49.3, 0.81, 0.60, true, false};
//	ciudades[3] = CiudadLogistica{3, "Corpen", -71.6, -47.1, 0.28, 0.37, true, false};
//	ciudades[4] = CiudadLogistica{4, "Alke Guer", -69.6, -46.1, 0.60, 0.18, true, false};
//	ciudades[5] = CiudadLogistica{5, "Gendarme Barreto", -64.8, -46.6, 0.92, 0.43, false, true};
//	ciudades[6] = CiudadLogistica{6, "Pico Truncado", -67.7, -46.9, 0.64, 0.27, false, true};
//	ciudades[7] = CiudadLogistica{7, "Luis Piedrabuena", -68.9, -51.5, 0.43, 0.93, false, true};
}

void SistemaLogistico::inicializarRutas() {
//	for (int i = 0; i < CANTIDAD_CIUDADES; i++) {
//		for (int j = 0; j < CANTIDAD_CIUDADES; j++) {
//			rutas[i][j] = SIN_RUTA;
//		}
//	}
//
//	agregarRuta(0, 1);
//	agregarRuta(0, 7);
//	agregarRuta(0, 3);
//	agregarRuta(1, 2);
//	agregarRuta(1, 3);
//	agregarRuta(1, 4);
//	agregarRuta(1, 7);
//	agregarRuta(2, 5);
//	agregarRuta(2, 6);
//	agregarRuta(2, 7);
//	agregarRuta(3, 4);
//	agregarRuta(3, 6);
//	agregarRuta(4, 5);
//	agregarRuta(4, 6);
//	agregarRuta(5, 6);
}
