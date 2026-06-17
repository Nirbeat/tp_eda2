#ifndef STRUCTS_H
#define STRUCTS_H

struct Coordenadas {
  int x;
  int y;
};

struct ResultadoRuta{
	int cantidadNodosRecorridos;
	int* indices;
	int distancia;
};
#endif