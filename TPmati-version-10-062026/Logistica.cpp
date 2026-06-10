#include "Logistica.h"

#include <cmath>
#include <limits>
#include <sstream>

namespace {
	const double SIN_RUTA = -1.0;
	const double RADIO_TIERRA_KM = 6371.0;

	double aRadianes(double grados) {
		return grados * 3.14159265358979323846 / 180.0;
	}
}

SistemaLogistico::SistemaLogistico()
	: cantidadHistorial(0) {
	inicializarCiudades();
	inicializarRutas();
}

void SistemaLogistico::inicializarCiudades() {
	ciudades[0] = CiudadLogistica{0, "Calafate", -72.3, -50.3, 0.34, 0.77, true, false};
	ciudades[1] = CiudadLogistica{1, "Gobernador Gregores", -70.2, -48.8, 0.50, 0.52, true, false};
	ciudades[2] = CiudadLogistica{2, "Puerto San Julian", -67.7, -49.3, 0.81, 0.60, true, false};
	ciudades[3] = CiudadLogistica{3, "Corpen", -71.6, -47.1, 0.28, 0.37, true, false};
	ciudades[4] = CiudadLogistica{4, "Alke Guer", -69.6, -46.1, 0.60, 0.18, true, false};
	ciudades[5] = CiudadLogistica{5, "Gendarme Barreto", -64.8, -46.6, 0.92, 0.43, false, true};
	ciudades[6] = CiudadLogistica{6, "Pico Truncado", -67.7, -46.9, 0.64, 0.27, false, true};
	ciudades[7] = CiudadLogistica{7, "Luis Piedrabuena", -68.9, -51.5, 0.43, 0.93, false, true};
}

void SistemaLogistico::inicializarRutas() {
	for (int i = 0; i < CANTIDAD_CIUDADES; i++) {
		for (int j = 0; j < CANTIDAD_CIUDADES; j++) {
			rutas[i][j] = SIN_RUTA;
		}
	}

	agregarRuta(0, 1);
	agregarRuta(0, 7);
	agregarRuta(0, 3);
	agregarRuta(1, 2);
	agregarRuta(1, 3);
	agregarRuta(1, 4);
	agregarRuta(1, 7);
	agregarRuta(2, 5);
	agregarRuta(2, 6);
	agregarRuta(2, 7);
	agregarRuta(3, 4);
	agregarRuta(3, 6);
	agregarRuta(4, 5);
	agregarRuta(4, 6);
	agregarRuta(5, 6);
}

void SistemaLogistico::agregarRuta(int origen, int destino) {
	double distancia = distanciaEntreCoordenadas(origen, destino);
	rutas[origen][destino] = distancia;
	rutas[destino][origen] = distancia;
}

double SistemaLogistico::distanciaEntreCoordenadas(int origen, int destino) const {
	double lon1 = aRadianes(ciudades[origen].x);
	double lat1 = aRadianes(ciudades[origen].y);
	double lon2 = aRadianes(ciudades[destino].x);
	double lat2 = aRadianes(ciudades[destino].y);

	double dlon = lon2 - lon1;
	double dlat = lat2 - lat1;
	double a = std::sin(dlat / 2.0) * std::sin(dlat / 2.0) +
			   std::cos(lat1) * std::cos(lat2) *
			   std::sin(dlon / 2.0) * std::sin(dlon / 2.0);
	double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));
	return RADIO_TIERRA_KM * c;
}

int SistemaLogistico::cantidadCiudades() const {
	return CANTIDAD_CIUDADES;
}

const CiudadLogistica& SistemaLogistico::obtenerCiudad(int id) const {
	return ciudades[id];
}

bool SistemaLogistico::ciudadExiste(int id) const {
	return id >= 0 && id < CANTIDAD_CIUDADES;
}

bool SistemaLogistico::ciudadActiva(int id) const {
	return ciudadExiste(id) && ciudades[id].activa;
}

bool SistemaLogistico::ciudadEditable(int id) const {
	return ciudadExiste(id) && ciudades[id].editable;
}

bool SistemaLogistico::rutaActiva(int origen, int destino) const {
	return ciudadActiva(origen) &&
		   ciudadActiva(destino) &&
		   rutas[origen][destino] >= 0.0;
}

bool SistemaLogistico::darAltaCiudad(int id) {
	if (!ciudadEditable(id)) {
		return false;
	}

	ciudades[id].activa = true;
	return true;
}

bool SistemaLogistico::darBajaCiudad(int id) {
	if (!ciudadEditable(id)) {
		return false;
	}

	ciudades[id].activa = false;
	return true;
}

ResultadoRuta SistemaLogistico::calcularRutaOptima(int origen, int destino) {
	ResultadoRuta resultado;
	resultado.encontrada = false;
	resultado.cantidadCiudades = 0;
	resultado.distanciaKm = 0.0;

	if (!ciudadExiste(origen) || !ciudadExiste(destino)) {
		resultado.mensaje = "Ciudad inexistente.";
		return resultado;
	}

	if (!ciudadActiva(origen) || !ciudadActiva(destino)) {
		resultado.mensaje = "Origen y destino deben estar dados de alta.";
		return resultado;
	}

	if (origen == destino) {
		resultado.mensaje = "El origen y el destino no pueden ser la misma ciudad.";
		return resultado;
	}

	double distancia[CANTIDAD_CIUDADES];
	bool visitado[CANTIDAD_CIUDADES];
	int anterior[CANTIDAD_CIUDADES];

	for (int i = 0; i < CANTIDAD_CIUDADES; i++) {
		distancia[i] = std::numeric_limits<double>::max();
		visitado[i] = false;
		anterior[i] = -1;
	}

	distancia[origen] = 0.0;

	for (int paso = 0; paso < CANTIDAD_CIUDADES; paso++) {
		int actual = -1;
		double mejor = std::numeric_limits<double>::max();

		for (int i = 0; i < CANTIDAD_CIUDADES; i++) {
			if (!visitado[i] && ciudadActiva(i) && distancia[i] < mejor) {
				mejor = distancia[i];
				actual = i;
			}
		}

		if (actual == -1) {
			break;
		}

		if (actual == destino) {
			break;
		}

		visitado[actual] = true;

		for (int vecino = 0; vecino < CANTIDAD_CIUDADES; vecino++) {
			if (rutas[actual][vecino] >= 0.0 && ciudadActiva(vecino)) {
				double nuevaDistancia = distancia[actual] + rutas[actual][vecino];
				if (nuevaDistancia < distancia[vecino]) {
					distancia[vecino] = nuevaDistancia;
					anterior[vecino] = actual;
				}
			}
		}
	}

	if (distancia[destino] == std::numeric_limits<double>::max()) {
		resultado.mensaje = "No existe una ruta activa entre esas ciudades.";
		return resultado;
	}

	int invertido[MAX_RUTAS_CAMINO];
	int cantidad = 0;
	for (int actual = destino; actual != -1 && cantidad < MAX_RUTAS_CAMINO; actual = anterior[actual]) {
		invertido[cantidad++] = actual;
	}

	for (int i = 0; i < cantidad; i++) {
		resultado.camino[i] = invertido[cantidad - 1 - i];
	}

	resultado.encontrada = true;
	resultado.cantidadCiudades = cantidad;
	resultado.distanciaKm = distancia[destino];
	resultado.mensaje = "Ruta encontrada.";
	return resultado;
}

std::string SistemaLogistico::describirRuta(const ResultadoRuta &resultado) const {
	if (!resultado.encontrada) {
		return resultado.mensaje;
	}

	std::ostringstream salida;
	for (int i = 0; i < resultado.cantidadCiudades; i++) {
		if (i > 0) {
			salida << " -> ";
		}
		salida << ciudades[resultado.camino[i]].nombre;
	}

	salida.setf(std::ios::fixed);
	salida.precision(1);
	salida << "\nDistancia aproximada: " << resultado.distanciaKm << " km";
	return salida.str();
}

void SistemaLogistico::guardarEnHistorial(int origen, int destino, const ResultadoRuta &resultado) {
	if (!resultado.encontrada || cantidadHistorial >= MAX_HISTORIAL) {
		return;
	}

	historial[cantidadHistorial].origen = origen;
	historial[cantidadHistorial].destino = destino;
	historial[cantidadHistorial].distanciaKm = resultado.distanciaKm;
	historial[cantidadHistorial].descripcion = describirRuta(resultado);
	cantidadHistorial++;
}

int SistemaLogistico::obtenerCantidadHistorial() const {
	return cantidadHistorial;
}

const RegistroHistorial& SistemaLogistico::obtenerHistorial(int indice) const {
	return historial[indice];
}
