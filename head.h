#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <windows.h>

using namespace std;

/*
===============================================================================
								CONFIGURACION GENERAL
===============================================================================

El programa simula un sistema de rutas entre ciudades.

El mapa es una matriz de 10x10 donde:
- '0' = zona bloqueada
- '1' = avenida transitable
- 'A'..'E' = ciudades

Luego se utiliza DFS (Depth First Search) para encontrar TODOS los caminos
posibles entre dos ciudades.

===============================================================================
*/

#define NODOS 5
#define FILAS_MAPA 10
#define COLUMNAS_MAPA 10
#define MAX_CASILLAS 100
#define MAX_CAMINOS 20
#define KM_POR_CASILLA 100
#define VELOCIDAD_KM_H 100

#define BLOQUEADO '0'
#define AVENIDA '1'

/*
===============================================================================
								COLORES DE CONSOLA
===============================================================================
*/

#define COLOR_NORMAL 7
#define COLOR_CIUDAD 79
#define COLOR_AVENIDA 42
#define COLOR_BLOQUEADO_1 96
#define COLOR_BLOQUEADO_2 110
#define COLOR_CAMINO_SELECCIONADO 191
#define COLOR_CAMINO_ALTERNATIVO 31

/*
===============================================================================
								CIUDADES
===============================================================================

A = Perito Moreno
B = Puerto Deseado
C = Gregores
D = Puerto Santa Cruz
E = El Calafate

===============================================================================
*/

/*
Punto:
Representa una coordenada del mapa.

Ejemplo:
mapa[y][x]

y = fila
x = columna
*/
struct Punto {
	int y;
	int x;
};

/*
Camino:
Guarda una secuencia de puntos recorridos.

Ejemplo:
(A -> avenida -> avenida -> ciudad destino)
*/
struct Camino {
	Punto puntos[MAX_CASILLAS];
	int tam;
};


#endif