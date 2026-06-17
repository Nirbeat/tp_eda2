#include "ciudad.h"
#include <cstring>

Ciudad::Ciudad() {
    id = -1;
	nombre = "";
	coordenadas.x = 0;
	coordenadas.y = 0;
    activa = true;
}

Ciudad::Ciudad(int _id, const std::string& _nombre, Coordenadas _coordenadas) {
    id = _id;
	nombre = _nombre;
    coordenadas = _coordenadas;
    activa = true;
}

std::string Ciudad::obtenerNombre(){
    return nombre;
}
struct Coordenadas Ciudad::obtenerCoordenadas() {
return coordenadas;
}
int Ciudad::obtenerId() { return id; }
bool Ciudad::obtenerEstado() { return activa; }
void Ciudad::cambiarEstado() { activa = !activa; }
