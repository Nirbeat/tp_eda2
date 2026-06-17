#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <limits>
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
#define MAX_CAMINOS 5
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

struct Punto {
    int y;
    int x;
};

struct Camino {
    Punto puntos[MAX_CASILLAS];
    int tam;
};

/*
===============================================================================
                        FUNCIONES GENERALES
===============================================================================
*/

void limpiarPantalla() {
    system("cls");
}

void cambiarColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void colorNormal() {
    cambiarColor(COLOR_NORMAL);
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarCiudades() {

    cout << "===== CIUDADES =====\n\n";

    cout << "A = Perito Moreno\n";
    cout << "B = Puerto Deseado\n";
    cout << "C = Gregores\n";
    cout << "D = Puerto Santa Cruz\n";
    cout << "E = El Calafate\n";
}

string nombreCiudad(char letra) {

    switch (letra) {

    case 'A':
        return "Perito Moreno";

    case 'B':
        return "Puerto Deseado";

    case 'C':
        return "Gregores";

    case 'D':
        return "Puerto Santa Cruz";

    case 'E':
        return "El Calafate";

    default:
        return "Ciudad desconocida";
    }
}

bool letraCiudadValida(char letra) {

    letra = toupper(letra);

    return letra >= 'A' && letra <= 'E';
}

bool esCiudad(char valor) {
    return valor >= 'A' && valor <= 'E';
}

/*
===============================================================================
                        INICIALIZACION DEL MAPA
===============================================================================
*/

void inicializarMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]) {

    for (int y = 0; y < FILAS_MAPA; y++) {

        for (int x = 0; x < COLUMNAS_MAPA; x++) {

            mapa[y][x] = BLOQUEADO;
        }
    }
}

void cargarAvenidasEnMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]) {

    for (int x = 2; x <= 7; x++) {
        mapa[1][x] = AVENIDA;
    }

    for (int y = 2; y <= 4; y++) {
        mapa[y][4] = AVENIDA;
    }

    for (int x = 5; x <= 8; x++) {
        mapa[5][x] = AVENIDA;
    }

    for (int y = 2; y <= 6; y++) {
        mapa[y][8] = AVENIDA;
    }

    for (int y = 6; y <= 8; y++) {
        mapa[y][4] = AVENIDA;
    }

    mapa[8][3] = AVENIDA;
}

void cargarCiudadesEnMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]) {

    mapa[1][1] = 'A';
    mapa[1][8] = 'B';
    mapa[5][4] = 'C';
    mapa[7][8] = 'D';
    mapa[8][2] = 'E';
}

void cargarMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]) {

    inicializarMapa(mapa);

    cargarAvenidasEnMapa(mapa);

    cargarCiudadesEnMapa(mapa);
}

bool buscarCoordenadaCiudad(
                                char mapa[FILAS_MAPA][COLUMNAS_MAPA],
                                char ciudad,
                                Punto &posicion
                            ) {

    for (int y = 0; y < FILAS_MAPA; y++) {

        for (int x = 0; x < COLUMNAS_MAPA; x++) {

            if (mapa[y][x] == ciudad) {

                posicion.y = y;
                posicion.x = x;

                return true;
            }
        }
    }

    return false;
}

bool estaDentroDelMapa(int y, int x) {

    return y >= 0 &&
           y < FILAS_MAPA &&
           x >= 0 &&
           x < COLUMNAS_MAPA;
}

bool esTransitable(char valor) {

    return valor == AVENIDA || esCiudad(valor);
}

bool puntoIgual(Punto a, Punto b) {

    return a.y == b.y &&
           a.x == b.x;
}

bool puntoEnCamino(Camino camino, int y, int x) {

    for (int i = 0; i < camino.tam; i++) {

        if (camino.puntos[i].y == y &&
            camino.puntos[i].x == x) {

            return true;
        }
    }

    return false;
}

bool puntoEnAlgunaAlternativa(
                                Camino caminos[MAX_CAMINOS],
                                int cantidad,
                                int seleccionado,
                                int y,
                                int x
                              ) {

    for (int i = 0; i < cantidad; i++) {

        if (i != seleccionado &&
            puntoEnCamino(caminos[i], y, x)) {

            return true;
        }
    }

    return false;
}

void guardarCamino(
                    Camino caminos[MAX_CAMINOS],
                    int &cantidad,
                    Camino actual
                  ) {

    if (cantidad >= MAX_CAMINOS) {
        return;
    }

    caminos[cantidad] = actual;

    cantidad++;
}

/*
===============================================================================
                        DFS (Depth First Search)
===============================================================================
*/

void buscarCaminosDFS(
                        char mapa[FILAS_MAPA][COLUMNAS_MAPA],
                        Punto actual,
                        Punto destino,
                        int visitado[FILAS_MAPA][COLUMNAS_MAPA],
                        Camino &caminoActual,
                        Camino caminos[MAX_CAMINOS],
                        int &cantidadCaminos
                      ) {

    if (cantidadCaminos >= MAX_CAMINOS ||
        caminoActual.tam >= MAX_CASILLAS) {

        return;
    }

    caminoActual.puntos[caminoActual.tam++] = actual;

    visitado[actual.y][actual.x] = 1;

    if (puntoIgual(actual, destino)) {

        guardarCamino(caminos, cantidadCaminos, caminoActual);

    } else {

        int dy[4] = {-1, 0, 1, 0};
        int dx[4] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {

            int nuevoY = actual.y + dy[i];
            int nuevoX = actual.x + dx[i];

            if (estaDentroDelMapa(nuevoY, nuevoX) &&
                visitado[nuevoY][nuevoX] == 0 &&
                esTransitable(mapa[nuevoY][nuevoX])) {

                Punto siguiente;

                siguiente.y = nuevoY;
                siguiente.x = nuevoX;

                buscarCaminosDFS(
                                    mapa,
                                    siguiente,
                                    destino,
                                    visitado,
                                    caminoActual,
                                    caminos,
                                    cantidadCaminos
                                 );
            }
        }
    }

    visitado[actual.y][actual.x] = 0;

    caminoActual.tam--;
}

/*
===============================================================================
                        CALCULOS
===============================================================================
*/

void ordenarCaminosPorDistancia(
                                    Camino caminos[MAX_CAMINOS],
                                    int cantidad
                               ) {

    for (int i = 0; i < cantidad - 1; i++) {

        for (int j = i + 1; j < cantidad; j++) {

            if (caminos[j].tam < caminos[i].tam) {

                Camino aux = caminos[i];

                caminos[i] = caminos[j];

                caminos[j] = aux;
            }
        }
    }
}

int calcularCasillasRecorridas(Camino camino) {

    return camino.tam - 1;
}

int calcularKilometros(Camino camino) {

    return calcularCasillasRecorridas(camino) * KM_POR_CASILLA;
}

int calcularHoras(Camino camino) {

    return calcularKilometros(camino) / VELOCIDAD_KM_H;
}

/*
===============================================================================
                            MOSTRAR MAPA
===============================================================================
*/

void mostrarCelda(
                    char mapa[FILAS_MAPA][COLUMNAS_MAPA],
                    Camino caminos[MAX_CAMINOS],
                    int cantidadCaminos,
                    int seleccionado,
                    int y,
                    int x
                 ) {

    char valor = mapa[y][x];

    if (esCiudad(valor)) {
    
        cambiarColor(COLOR_CIUDAD);
    
    } else if (seleccionado >= 0 &&
           puntoEnCamino(caminos[seleccionado], y, x)) {

    cambiarColor(COLOR_CAMINO_SELECCIONADO);

    } else if (puntoEnAlgunaAlternativa(
                                            caminos,
                                            cantidadCaminos,
                                            seleccionado,
                                            y,
                                            x
                                        )) {

        cambiarColor(COLOR_CAMINO_ALTERNATIVO);

    } else if (valor == AVENIDA) {

        cambiarColor(COLOR_AVENIDA);

    } else if ((y + x) % 2 == 0) {

        cambiarColor(COLOR_BLOQUEADO_1);

    } else {

        cambiarColor(COLOR_BLOQUEADO_2);
    }

    cout << setw(2) << valor << ' ';

    colorNormal();
}

void mostrarMapaVisual(
                            char mapa[FILAS_MAPA][COLUMNAS_MAPA],
                            Camino caminos[MAX_CAMINOS],
                            int cantidadCaminos,
                            int seleccionado
                       ) {

    cout << "Coordenadas: mapa[y][x]\n";

    cout << "Ciudades = rojo | "
         << "No caminos = amarillo | "
         << "Caminos = verde | "
         << "Camino seleccionado = celeste | "
         << "Caminos alternativos = azul\n\n";

    cout << "     ";

    for (int x = 0; x < COLUMNAS_MAPA; x++) {

        cout << setw(2) << x << ' ';
    }

    cout << endl;

    for (int y = 0; y < FILAS_MAPA; y++) {

        cout << setw(3) << y << "  ";

        for (int x = 0; x < COLUMNAS_MAPA; x++) {

            mostrarCelda(
                            mapa,
                            caminos,
                            cantidadCaminos,
                            seleccionado,
                            y,
                            x
                         );
        }

        cout << endl;
    }
}

void mostrarMapa() {

    char mapa[FILAS_MAPA][COLUMNAS_MAPA];

    Camino caminos[MAX_CAMINOS];

    cargarMapa(mapa);

    cout << "===== MAPA =====\n\n";

    mostrarCiudades();

    cout << endl;

    mostrarMapaVisual(mapa, caminos, 0, -1);
}

/*
===============================================================================
                        INFORMACION DE CAMINOS
===============================================================================
*/

void mostrarResumenCamino(
                            Camino camino,
                            char origen,
                            char destino
                          ) {

    cout << "Viaje confirmado: "
         << nombreCiudad(origen)
         << " -> "
         << nombreCiudad(destino)
         << endl;

    cout << "Casillas recorridas: "
         << calcularCasillasRecorridas(camino)
         << endl;

    cout << "Distancia aproximada: "
         << calcularKilometros(camino)
         << " km\n";

    cout << "Tiempo estimado: "
         << calcularHoras(camino)
         << " hs si va a "
         << VELOCIDAD_KM_H
         << " km/h\n";
}

void mostrarOpcionesDeCamino(
                                Camino caminos[MAX_CAMINOS],
                                int cantidadCaminos
                             ) {

    cout << "===== CAMINOS ENCONTRADOS =====\n\n";

    for (int i = 0; i < cantidadCaminos; i++) {

        cout << i + 1 << " = Camino " << i + 1;

        if (i == 0) {
            cout << " *MAS CORTO*";
        }

        cout << " | "
             << calcularCasillasRecorridas(caminos[i])
             << " casillas";

        cout << " | "
             << calcularKilometros(caminos[i])
             << " km";

        cout << " | "
             << calcularHoras(caminos[i])
             << " hs\n";
    }

    cout << "X = Volver al menu principal\n";
}

/*
===============================================================================
                        MENU DE CAMINOS
===============================================================================
*/

void menuCaminosEncontrados(
                                char mapa[FILAS_MAPA][COLUMNAS_MAPA],
                                Camino caminos[MAX_CAMINOS],
                                int cantidadCaminos,
                                char origen,
                                char destino
                           ) {

    char opcion;

    int seleccionado = 0;

    do {

        limpiarPantalla();

        mostrarCiudades();

        cout << "\n";

        mostrarMapaVisual(
                            mapa,
                            caminos,
                            cantidadCaminos,
                            seleccionado
                          );

        cout << "\nCamino mostrado actualmente: "
             << seleccionado + 1
             << "\n\n";

        mostrarResumenCamino(
                                caminos[seleccionado],
                                origen,
                                destino
                             );

        cout << "\n";

        mostrarOpcionesDeCamino(
                                    caminos,
                                    cantidadCaminos
                                );

        cout << "\nSeleccione un camino (1-5)";
        cout << "\nX = Volver al menu principal";

        cout << "\n\n>> ";

        cin >> opcion;

        opcion = toupper(opcion);

        if (opcion >= '1' && opcion <= '5') {

            int nuevoSeleccionado = opcion - '1';

            if (nuevoSeleccionado >= 0 &&
                nuevoSeleccionado < cantidadCaminos) {

                seleccionado = nuevoSeleccionado;
            }
        }

    } while (opcion != 'X');
}

/*
===============================================================================
                        BUSQUEDA PRINCIPAL
===============================================================================
*/

void buscarConexion() {

    char mapa[FILAS_MAPA][COLUMNAS_MAPA];

    Camino caminos[MAX_CAMINOS];

    Camino caminoActual;

    int visitado[FILAS_MAPA][COLUMNAS_MAPA];

    int cantidadCaminos = 0;

    char origenLetra;
    char destinoLetra;

    Punto origen;
    Punto destino;

    cargarMapa(mapa);

    caminoActual.tam = 0;

    for (int y = 0; y < FILAS_MAPA; y++) {

        for (int x = 0; x < COLUMNAS_MAPA; x++) {

            visitado[y][x] = 0;
        }
    }

    mostrarCiudades();

    cout << "\nIngrese ciudad origen (A-E): ";
    cin >> origenLetra;

    cout << "Ingrese ciudad destino (A-E): ";
    cin >> destinoLetra;

    origenLetra = toupper(origenLetra);
    destinoLetra = toupper(destinoLetra);

    if (!letraCiudadValida(origenLetra) ||
        !letraCiudadValida(destinoLetra)) {

        cout << "\nERROR: Ciudad invalida.\n";

        cout << "Solo puede ingresar letras entre A y E.\n";

        return;
    }

    if (origenLetra == destinoLetra) {

        cout << "\nERROR: "
             << "El origen y destino no pueden ser iguales.\n";

        return;
    }

    if (!buscarCoordenadaCiudad(mapa, origenLetra, origen) ||
        !buscarCoordenadaCiudad(mapa, destinoLetra, destino)) {

        cout << "\nERROR: "
             << "No se encontro alguna ciudad en el mapa.\n";

        return;
    }

    buscarCaminosDFS(
                        mapa,
                        origen,
                        destino,
                        visitado,
                        caminoActual,
                        caminos,
                        cantidadCaminos
                     );

    ordenarCaminosPorDistancia(
                                    caminos,
                                    cantidadCaminos
                               );

    if (cantidadCaminos == 0) {

        cout << "\nNo existe camino entre esas ciudades.\n\n";

        mostrarMapaVisual(
                            mapa,
                            caminos,
                            0,
                            -1
                          );

        return;
    }

    menuCaminosEncontrados(
                                mapa,
                                caminos,
                                cantidadCaminos,
                                origenLetra,
                                destinoLetra
                           );
}

/*
===============================================================================
                            MENU PRINCIPAL
===============================================================================
*/

void mostrarMenu() {

    cout << "===== MENU PRINCIPAL =====\n\n";

    cout << "0 = Ver mapa\n";

    cout << "1 = Elegir viaje\n";

    cout << "X = Finalizar\n\n";

    cout << "Ingrese una opcion: ";
}

/*
===============================================================================
                                MAIN
===============================================================================
*/

int main() {

    char opcion;

    do {

        limpiarPantalla();

        mostrarMenu();

        cin >> opcion;

        opcion = toupper(opcion);

        limpiarPantalla();

        switch (opcion) {

        case '0':

            mostrarMapa();

            pausar();

            break;

        case '1':

            buscarConexion();

            pausar();

            break;

        case 'X':

            cout << "Programa finalizado.\n";

            break;

        default:

            cout << "ERROR: Opcion invalida.\n";

            pausar();

            break;
        }

    } while (opcion != 'X');

    colorNormal();

    return 0;
}
