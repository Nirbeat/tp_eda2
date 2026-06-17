#include "mapa.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

// Constructor
Mapa::Mapa() {
  // Inicializamos punteros en nullptr para evitar problemas en el destructor
  listaCiudades = nullptr;
  matrizAdyacencia = nullptr;

  // 1-se lee el archivo de la matriz de adyacencia y se cuentan la cantidad
  // de registros segun saltos de linea
  std::ifstream matriz("archivos/matriz.dat");
  if (!matriz.is_open()) {
    matriz.open("archivos/matriz.dat");
  }

  int lineas = 0;
  std::string linea;
  while (std::getline(matriz, linea)) {
    lineas++;
  }

  cantidadCiudades = lineas;

  // === 1. PEDIMOS LA MEMORIA PARA LA MATRIZ DE ADYACENCIA ===
  matrizAdyacencia = new int *[cantidadCiudades];
  for (int i = 0; i < cantidadCiudades; i++) {
    matrizAdyacencia[i] = new int[cantidadCiudades];
  }

  matriz.clear();
  matriz.seekg(0, std::ios::beg);

  int fila = 0;
  while (std::getline(matriz, linea)) {
	std::stringstream ss(linea);
    int valor;
	int columna = 0;

	// el ">>" se saltea espacios en blanco y tabs
	while (ss >> valor && columna < cantidadCiudades) {
      matrizAdyacencia[fila][columna] = valor;
      columna++;
    }
    fila++;
  }

  matriz.close();

  listaCiudades = new Ciudad[cantidadCiudades];

  std::ifstream archCiudades("archivos/ciudades.dat");

  if (archCiudades.is_open()) {
    std::string lineaCiudad;
    int idx = 0;

    while (std::getline(archCiudades, lineaCiudad) && idx < cantidadCiudades) {
      // 1. Convertimos la línea de texto en un "flujo de datos" de C++
      std::stringstream fila(lineaCiudad);

      // Variables temporales para extraer los datos como strings primero
      std::string strId, nombre, strX, strY;

      // 2. Extraemos cada pedazo usando el ';' como guillotina
      std::getline(fila, strId, ';');  // Saca el ID como texto
      std::getline(fila, nombre, ';'); // Saca el Nombre
      std::getline(fila, strX, ';');   // Saca la X como texto
      std::getline(fila, strY, ';');   // Saca la Y como texto

      // 3. Convertimos los strings a los números reales que corresponden
      int id = std::stoi(strId); // stoi = String To Integer
      int x = std::stoi(strX);
      int y = std::stoi(strY);
      // 4. Armamos las coordenadas e instanciamos la ciudad en el array
      Coordenadas coords = {(int)x, (int)y};
      listaCiudades[idx] = Ciudad(id, nombre, coords);
      idx++; // Avanzamos al siguiente casillero del array dinámico
    }
    archCiudades.close();
  }
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

    if (listaCiudades[i].obtenerEstado() == true) {

      ciudadesInterfaz[indiceUI] = listaCiudades[i];
      indiceUI++;
    }
  }
}

int Mapa::obtenerCantidadCiudades() { return cantidadCiudades; }

int **Mapa::obtenerMatrizAdyacencia() { return matrizAdyacencia; }
