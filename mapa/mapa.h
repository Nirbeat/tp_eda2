#ifndef MAPA_H
#define MAPA_H

#include "../ciudad/ciudad.h"


class Mapa {

private:
	Ciudad* listaCiudades;
	int cantidadCiudades;
	int** matrizAdyacencia;

public:
	Mapa();
	~Mapa();

    void actualizarCantidadCiudades(int valor);//setter cantidadCiudades
	int obtenerCantidadCiudades(); //getter de cantidadCiudades

	int** obtenerMatrizAdyacencia(); //getter matrizAdyacencia
	void pasarListaCiudades(Ciudad arrayDestino[]); //copia lista a la UI
	int obtenerDistanciaCiudades(int idOrigen, int idDestino); //

	void agregarCiudad();
	void eliminarCiudad(int idCiudad);
};

#endif