#ifndef MAPA_H
#define MAPA_H

#include "../ciudad/ciudad.h"
#include <string>

using namespace std;

// Esta constante fija es obligatoria para la matriz estática
const int MAX_MATRIZ = 7;

class Mapa {
private:
    Ciudad* listaCiudades; // Puntero para el array dinámico (este SÍ se maneja en ejecución)
    int cantidadActual;    // Cuántas ciudades reales hay en el mapa (ej: arranca en 1)
    
    // CORREGIDO: Usamos MAX_MATRIZ (7) y NO cantidadActual
    int matrizAdyacencia[MAX_MATRIZ][MAX_MATRIZ];

public:
    Mapa();
    ~Mapa(); 

    void leerArchivo();
    int obtenerCiudades(Ciudad arrayDestino[]) const;
    void cargarMatriz();
    int distanciaNodos(int idOrigen, int idDestino);
    void ubicarNodos(); 
};

#endif