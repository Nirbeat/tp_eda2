#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "head.h"

void limpiarPantalla();

void cambiarColor(int color);

void colorNormal();

void pausar();

void mostrarCiudades();

string nombreCiudad(char letra);

bool letraCiudadValida(char letra);

bool esCiudad(char valor);

void inicializarMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]);

void cargarAvenidasEnMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]);

void cargarCiudadesEnMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]);

void cargarMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]);

bool buscarCoordenadaCiudad(
	char mapa[FILAS_MAPA][COLUMNAS_MAPA],
	char ciudad,
	Punto &posicion
);

bool estaDentroDelMapa(int y, int x);

bool esTransitable(char valor);

bool puntoIgual(Punto a, Punto b);

bool puntoEnCamino(Camino camino, int y, int x);

bool puntoEnAlgunaAlternativa(
	Camino caminos[MAX_CAMINOS],
	int cantidad,
	int seleccionado,
	int y,
	int x
);

void guardarCamino(
	Camino caminos[MAX_CAMINOS],
	int &cantidad,
	Camino actual
);

void buscarCaminosDFS(
	char mapa[FILAS_MAPA][COLUMNAS_MAPA],
	Punto actual,
	Punto destino,
	int visitado[FILAS_MAPA][COLUMNAS_MAPA],
	Camino &caminoActual,
	Camino caminos[MAX_CAMINOS],
	int &cantidadCaminos
);

void ordenarCaminosPorDistancia(
	Camino caminos[MAX_CAMINOS],
	int cantidad
);

int calcularCasillasRecorridas(Camino camino);

int calcularKilometros(Camino camino);

int calcularHoras(Camino camino);

void mostrarCelda(
	char mapa[FILAS_MAPA][COLUMNAS_MAPA],
	Camino caminos[MAX_CAMINOS],
	int cantidadCaminos,
	int seleccionado,
	int y,
	int x
);

void mostrarMapaVisual(
	char mapa[FILAS_MAPA][COLUMNAS_MAPA],
	Camino caminos[MAX_CAMINOS],
	int cantidadCaminos,
	int seleccionado
);

void mostrarMapa();

void mostrarResumenCamino(
	Camino camino,
	char origen,
	char destino
);

void mostrarOpcionesDeCamino(
	Camino caminos[MAX_CAMINOS],
	int cantidadCaminos
);

void menuCaminosEncontrados(
	char mapa[FILAS_MAPA][COLUMNAS_MAPA],
	Camino caminos[MAX_CAMINOS],
	int cantidadCaminos,
	char origen,
	char destino
);

void buscarConexion();

void mostrarMenu();

#endif