#include "mapa.h"

// PARA LAS 7 CIUDADES QUE PROPUSE, ESTA MATRIZ YA ESTARÍA COMPLETA
// PROPONGO, CUANDO SE HAGA EL ALGORITMO, QUE SE PRUEBE PRIMERO SOLO
// ENTRE LAS 3 PRINCIPALES (INDICES DEL 0 AL 2), PROBAR CORTAR LA CONEXION
// Y VER QUE BUSQUE EL CAMINO; LUEGO AGREGAR UNA 4TA CIUDAD (NODO INTERMEDIO)
// Y VER QUE LA USE EN VEZ DE USAR EL NODO PRINCIPAL (QUE ESTARÍA MÁS LEJOS)
// SI EN ESE CASO ANDA, DEBERIA FUNCIONAR CON LAS 7 CIUDADES; SI ANDA CON LAS
// 7, HACEMOS LA MATRIZ DE TODAS LAS QUE PROPUSO MATI Y DEBERIA ANDAR IGUAL
void Mapa::setMatriz() {
  // -1 INDICA QUE NO HAY CONEXION
  int matriz[7][7] = {
      {0, 335, 504, 314, 277, 105, -1}, {335, 0, 312, 122, -1, -1, 607},
      {504, 312, 0, -1, 331, 302, 338}, {314, 122, -1, 0, -1, -1, -1},
      {277, -1, 331, -1, 0, -1, -1},    {105, -1, 302, -1, -1, 0, -1},
      {-1, 607, 338, -1, -1, -1, 0}};

  for (int i = 0; i < 7; i++) {
    for (int j = 0; i < 7; i++) {
      this->matrizAdyacencia[i][j] = matriz[i][j];
    }
  }
}

// ESTE METODO NOS PERMITE CALCULAR LA DISTANCIA NODO A NODO, SE DEBERIA
// LLAMAR SIEMPRE QUE SE ENCUENTREN DOS NODOS ADYACENTES
int Mapa::distanciaNodos(int idOrigen, int idDestino) {
  return this->matrizAdyacencia[idOrigen][idDestino];
}

// ESTE METODO CARGA LOS NODOS
void Mapa::setNodos() {

  // con este va a haber que pelearse un poco porque tenemos que:
  // 1- o bien leer de un archivo
  // 2- o bien hardcodear las ciduades en la carga

  // ESTE CODIGO CLARAMENTE NO FUNCIONA PERO ES LO QUE HARIA EL METODO
  //   this->nodos = {
  //       {"calafate", {0, 0}, 0},          {"gobernador gregores", {0, 0}, 1},
  //       {"puerto san julian", {0, 0}, 2}, {"corpen", {0, 0}, 3},
  //       {"alke guer", {0, 0}, 4},         {"gendarme barreto", {0, 0}, 5},
  //       {"pico truncado", {0, 0}, 6}};
}

// ESTOS DOS MÉTODOS QUE SIGUEN NO SE SI IMPLEMENTARLOS ACA LLAMANDO A LA
// LIBRERIA QUE HACE LA UI O SI HACERLO DIRECTAMENTE EN LA LIBRERIA,
// PROBLEMAS DEL FUTURO, POR AHORA LO DEJAMOS
void Mapa::ubicarNodos() {
  // recorremos el array de nodos y ubicamos todas las ciudades en el mapa
  // extrayendo las coordenadas
}
void Mapa::cargarImagen() {
  // levantamos la imagen de fondo accediendo al this->imagen
}