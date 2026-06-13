#include "ciudad.h"
#include <cstring>

Ciudad::Ciudad() {
  id = -1;
  nombre[0] = '\0'; // Cadena vacía
  coordenadas.x = 0.0;
  coordenadas.y = 0.0;
  activa = true;
}

Ciudad::Ciudad(int _id, const char *_nombre, struct Coordenadas _coordenadas) {
  id = _id;
  coordenadas = _coordenadas;
  std::strcpy(nombre, _nombre);
}

char* Ciudad::obtenerNombre() { return nombre; }
struct Coordenadas Ciudad::obtenerCoordenadas() {
return coordenadas;
}
int Ciudad::obtenerId() { return id; }
bool Ciudad::obtenerEstado() { return activa; }
void Ciudad::cambiarEstado() { activa = !activa; }
