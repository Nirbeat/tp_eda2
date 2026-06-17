#ifndef LogisticaH
#define LogisticaH

#include <string>

const int CANTIDAD_CIUDADES = 8;
const int MAX_RUTAS_CAMINO = 8;
const int MAX_HISTORIAL = 50;

struct CiudadLogistica {
	int id;
	std::string nombre;
	double x;
	double y;
	double mapaX;
	double mapaY;
	bool activa;
	bool editable;
};

struct ResultadoRuta {
	bool encontrada;
	std::string mensaje;
	int camino[MAX_RUTAS_CAMINO];
	int cantidadCiudades;
	double distanciaKm;
};

struct RegistroHistorial {
	int origen;
	int destino;
	double distanciaKm;
	std::string descripcion;
};

class SistemaLogistico {
private:
	CiudadLogistica ciudades[CANTIDAD_CIUDADES];
	double rutas[CANTIDAD_CIUDADES][CANTIDAD_CIUDADES];
	RegistroHistorial historial[MAX_HISTORIAL];
	int cantidadHistorial;

	void inicializarCiudades();
	void inicializarRutas();
	void agregarRuta(int origen, int destino);
	double distanciaEntreCoordenadas(int origen, int destino) const;

public:
	SistemaLogistico();

	int cantidadCiudades() const;
	const CiudadLogistica& obtenerCiudad(int id) const;
	bool ciudadExiste(int id) const;
	bool ciudadActiva(int id) const;
	bool ciudadEditable(int id) const;
	bool rutaActiva(int origen, int destino) const;
	bool darAltaCiudad(int id);
	bool darBajaCiudad(int id);

	ResultadoRuta calcularRutaOptima(int origen, int destino);
	std::string describirRuta(const ResultadoRuta &resultado) const;
	void guardarEnHistorial(int origen, int destino, const ResultadoRuta &resultado);

	int obtenerCantidadHistorial() const;
	const RegistroHistorial& obtenerHistorial(int indice) const;
};

#endif
