#include "ciudad.h"
#include <cstring>

Ciudad::Ciudad() {
    id = -1;
    nombre[0] = '\0'; // Cadena vacía
    coordenadas.x = 0.0;
    coordenadas.y = 0.0;
}

Ciudad::Ciudad(int _id, const char* _nombre, struct Coordenadas _coordenadas) {
    id = _id;
    coordenadas = _coordenadas;
    std::strcpy(nombre, _nombre);
}