struct Coordenadas {
  int x;
  int y;
};

class Ciudad {
public:
  char nombre[30];
  struct Coordenadas coordenadas;
  int id;
};

int main() {
  //   for (int i = 0; i < 10; i++) {
  //     // SE ME HABIA OCURRIDO QUE ESTO PODRIA/DEBERIA IR EN ARCHIVO
  //     // Y CARGARLO LEYENDOLO? ASI SE PUEDE AUTOMATIZAR LA CARGA DEL ID
  //     Ciudad ciudad;
  //   }
  Ciudad ciudades[7] = {
      {"calafate", {0, 0}, 0},          {"gobernador gregores", {0, 0}, 1},
      {"puerto san julian", {0, 0}, 2}, {"corpen", {0, 0}, 3},
      {"alke guer", {0, 0}, 4},         {"gendarme barreto", {0, 0}, 5},
      {"pico truncado", {0, 0}, 6}};

  int matrizAdyacencia[7][7] = {
      {0, 335, 504, 314, 277, 105, -1}, {335, 0, 312, 122, -1, -1, 607},
      {504, 312, 0, -1, 331, 302, 338}, {314, 122, -1, 0, -1, -1, -1},
      {277, -1, 331, -1, 0, -1, -1},    {105, -1, 302, -1, -1, 0, -1},
      {-1, 607, 338, -1, -1, -1, 0}};

  return 0;
}
