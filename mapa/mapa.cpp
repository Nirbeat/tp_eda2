#include "mapa.h"
#include <cstddef> // Para usar NULL

// Constructor
Mapa::Mapa() {
	cantidadCiudades = 1; // Dejamos cargada 1 ciudad por ahora
	listaCiudades = new Ciudad[cantidadCiudades]; // Reservamos la memoria exacta
	leerArchivo(); // Llamamos a rellenar la ciudad [0]
}

// Destructor
Mapa::~Mapa() {
    if (listaCiudades != NULL) {
        delete[] listaCiudades;
    }
}

void Mapa::leerArchivo() {
    // Acá irá la lectura del archivo más adelante
}

int Mapa::obtenerCiudades(Ciudad ciudadesInterfaz[]) const {
	for (int i = 0; i < cantidadCiudades; i++) {
		ciudadesInterfaz[i] = listaCiudades[i];
	}
    return cantidadCiudades;
}

void Mapa::cargarMatriz() {
    int matriz[7][7] = {
        {0, 335, 504, 314, 277, 105, -1}, 
        {335, 0, 312, 122, -1, -1, 607},
        {504, 312, 0, -1, 331, 302, 338}, 
        {314, 122, -1, 0, -1, -1, -1},
        {277, -1, 331, -1, 0, -1, -1},    
        {105, -1, 302, -1, -1, 0, -1},
        {-1, 607, 338, -1, -1, -1, 0}
    };

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) { 
            this->matrizAdyacencia[i][j] = matriz[i][j];
        }
    }
}

int Mapa::distanciaNodos(int idOrigen, int idDestino) {
    return this->matrizAdyacencia[idOrigen][idDestino];
}