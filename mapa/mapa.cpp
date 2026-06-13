#include "mapa.h"

// Constructor
Mapa::Mapa() {
  // 1-se lee el archivo de la matriz de adyacencia y se cuentan la cantidad
  // de registros segun saltos de linea
  // 2-se asigna ese número a cantidadCiudades
  // 3-se cargan las ciudades en listaCiudades
  // 4-se carga el puntero en matrizaAdyacencia
}

// Destructor
Mapa::~Mapa() {
    if (listaCiudades != nullptr) {
        delete[] listaCiudades;
	}
	if (matrizAdyacencia != nullptr) {
        for (int i = 0; i < cantidadCiudades; i++) {
            delete[] matrizAdyacencia[i];
        }
		delete[] matrizAdyacencia;
    }
}

void Mapa::actualizarCantidadCiudades(int valor) {
  cantidadCiudades += valor; // se suma positivo o negativo, siempre 1
}

void Mapa::pasarListaCiudades(Ciudad ciudadesInterfaz[]) {
    // Usamos un contador propio para el array de la UI
    int indiceUI = 0;

    for (int i = 0; i < cantidadCiudades; i++) {
        // Accedemos con corchetes [i] y llamamos al método con ()
        if (listaCiudades[i].obtenerEstado() == true) {
            // Si está activa, la copiamos en la posición consecutiva de la UI
            ciudadesInterfaz[indiceUI] = listaCiudades[i];
            indiceUI++; // Recién acá avanzamos al siguiente casillero de la pantalla
        }
    }
}

  //mucha atencion aca: cuando se copia el array en la UI, hay que en base a ese
  //array dinamico, pintar las ciudades, tal como el trabajo que hizo Matias
  //hardcodeado. Lo que hay que hacer solamente es leer la data del array
  //que se copia mediante este método

int Mapa::obtenerCantidadCiudades() { return cantidadCiudades; }

int** Mapa::obtenerMatrizAdyacencia(){
	return matrizAdyacencia;
}
//esto que sigue ignorar por ahora
// void Mapa::cargarMatriz() {
//	int matriz[7][7] = {
//         {0, 335, 504, 314, 277, 105, -1},
//         {335, 0, 312, 122, -1, -1, 607},
//         {504, 312, 0, -1, 331, 302, 338},
//         {314, 122, -1, 0, -1, -1, -1},
//         {277, -1, 331, -1, 0, -1, -1},
//         {105, -1, 302, -1, -1, 0, -1},
//         {-1, 607, 338, -1, -1, -1, 0}
//     };
//
//     for (int i = 0; i < 7; i++) {
//         for (int j = 0; j < 7; j++) {
//             this->matrizAdyacencia[i][j] = matriz[i][j];
//         }
//     }
// }
