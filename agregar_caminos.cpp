// REGLAS: una arista no puede existir sin un nodo y un nodo no uede existir sin
// una arista que lo conecte.

#include <fstream>
#include <iostream>

// #include <cstring>
using namespace std;

struct camino {
  int ruta;
  char ciudad[20];
};

int main() {
  // Lista de caminos (ruta - ciudad)
  camino caminos[] = {// Ruta 3
                      {3, "Caleta Olivia"},
                      {3, "Fitz Roy"},
                      {3, "El Saldo"},
                      {3, "El Chalten"},
                      {3, "Guer Aike"},
                      {3, "Esperanza"},
                      {3, "Rio Gallegos"},

                      // Ruta 43
                      {43, "Perito Moreno"},
                      {43, "Pico Truncado"},
                      {43, "Rio Gallegos"},

                      // Ruta 40
                      {40, "Perito Moreno"},
                      {40, "Gregores"},
                      {40, "El Calafate"},
                      {40, "Rio Turbio"},
                      {40, "El Saldo"},
                      {40, "Esperanza"},

                      // Ruta 12
                      {12, "Caleta Olivia"},
                      {12, "Pico Truncado"},
                      {12, "Gregores"},

                      // Ruta 281
                      {281, "Fitz Roy"},
                      {281, "Puerto Deseado"},

                      // Ruta 47
                      {47, "Puerto Deseado"},
                      {47, "El Saldo"},

                      // Ruta 25
                      {25, "Gregores"},
                      {25, "El Chalten"},

                      // Ruta 288
                      {288, "Gregores"},
                      {288, "Guer Aike"},
                      {288, "Puerto Santa Cruz"},

                      // Ruta 9
                      {9, "El Calafate"},
                      {9, "Guer Aike"},

                      // Ruta 23
                      {23, "El Calafate"},
                      {23, "Piedra Buena"},

                      // Ruta 5
                      {5, "El Zurdo"},
                      {5, "Esperanza"}};

  ofstream archivo("caminos.dat", ios::binary | ios::app);

  if (!archivo) {
    cout << "Error al abrir el archivo.\n";
    return 1;
  }

  int total = sizeof(caminos) / sizeof(camino);

  for (int i = 0; i < total; i++) {
    archivo.write(reinterpret_cast<char *>(&caminos[i]), sizeof(camino));
  }

  archivo.close();

  cout << "caminos agregadas correctamente.\n";

  return 0;
}
