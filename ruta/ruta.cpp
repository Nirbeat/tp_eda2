#include "ruta.h"

// El constructor de Ruta recibe al Mapa que ya tiene todo cargado
Ruta::Ruta(Mapa *mapa) {
	this->mapa = mapa;
}

struct ResultadoRuta Ruta::encontrarRuta(int** matriz, int cantidadCiudades, int idOrigen, int idDestino){

}
//
//// Constructor: Inicializa en limpio y dispara el cálculo de Dijkstra inmediatamente
//Ruta::Ruta(int idOrigen, int idDestino, int** matrizAdyacencia, Ciudad listaCiudades[], int totalCiudadesSistema) {
//    caminoOptimo = nullptr;
//    cantidadCiudadesCamino = 0;
//    distanciaTotal = -1; // -1 significa "no hay ruta posible" por defecto
//
//    // Ejecutamos el algoritmo para rellenar nuestras propiedades privadas
//	calcularDijkstra(idOrigen, idDestino, matrizAdyacencia, listaCiudades, totalCiudadesSistema);
//}
//
//// Destructor: Limpieza de la memoria dinámica generada para este viaje específico
//Ruta::~Ruta() {
//    if (caminoOptimo != nullptr) {
//        delete[] caminoOptimo;
//    }
//}
//
//// Algoritmo de Dijkstra Puro aplicado a tu matriz dinámica
//void Ruta::calcularDijkstra(int idOrigen, int idDestino, int** matrizAdyacencia, Ciudad listaCiudades[], int totalCiudadesSistema) {
//
//    // Arrays auxiliares para el algoritmo (estáticos al tamaño total del mapa actual)
//    int* distancias = new int[totalCiudadesSistema];
//    bool* visitados = new bool[totalCiudadesSistema];
//    int* padres = new int[totalCiudadesSistema]; // Para reconstruir el camino al final
//
//    // Paso 1: Inicialización del estado del grafo
//    for (int i = 0; i < totalCiudadesSistema; i++) {
//        distancias[i] = 2000000000; // Un número gigante que simula "Infinito"
//        visitados[i] = false;
//        padres[i] = -1;
//    }
//
//    distancias[idOrigen] = 0; // La distancia a uno mismo es cero
//
//    // Paso 2: Bucle principal de Dijkstra
//    for (int count = 0; count < totalCiudadesSistema - 1; count++) {
//
//        // Encontramos el nodo con la distancia mínima que no haya sido visitado
//        int min = 2000000000;
//        int u = -1;
//
//        for (int v = 0; v < totalCiudadesSistema; v++) {
//            // Evaluamos solo ciudades existentes/activas en el sistema
//            if (listaCiudades[v].obtenerEstado() && !visitados[v] && distancias[v] <= min) {
//                min = distancias[v];
//                u = v;
//            }
//        }
//
//        // Si no encontramos ningún nodo accesible, rompemos el bucle
//        if (u == -1) break;
//
//        visitados[u] = true;
//
//        // Si ya llegamos al destino, no hace falta seguir explorando el resto del mapa
//        if (u == idDestino) break;
//
//        // Actualizamos las distancias de los vecinos del nodo 'u'
//        for (int v = 0; v < totalCiudadesSistema; v++) {
//            // Si está activa, no visitada, hay conexión directa (diferente de -1)
//            // y el nuevo camino acumulado es menor al que ya conocíamos:
//            if (listaCiudades[v].obtenerEstado() && !visitados[v] && matrizAdyacencia[u][v] != -1 && distancias[u] != 2000000000) {
//                if (distancias[u] + matrizAdyacencia[u][v] < distancias[v]) {
//                    distancias[v] = distancias[u] + matrizAdyacencia[u][v];
//                    padres[v] = u; // Guardamos de dónde vinimos para poder volver
//                }
//            }
//        }
//    }
//
//    // Guardamos el costo total si es que el destino es alcanzable
//    if (distancias[idDestino] != 2000000000) {
//        distanciaTotal = distancias[idDestino];
//
//        // Paso 3: Reconstrucción del camino óptimo hacia atrás
//        // Primero contamos cuántos nodos componen el camino final
//        int ciudadesEnCamino = 0;
//        int actual = idDestino;
//        while (actual != -1) {
//            ciudadesEnCamino++;
//            actual = padres[actual];
//        }
//
//        cantidadCiudadesCamino = ciudadesEnCamino;
//        caminoOptimo = new Ciudad[cantidadCiudadesCamino]; // Reservamos el espacio justo
//
//        // Llenamos el array dinámico al revés (desde el destino al origen)
//        actual = idDestino;
//        for (int i = cantidadCiudadesCamino - 1; i >= 0; i--) {
//
//            // Buscamos el objeto Ciudad correspondiente en el array del sistema
//            for (int j = 0; j < totalCiudadesSistema; j++) {
//                if (listaCiudades[j].obtenerId() == actual) {
//                    caminoOptimo[i] = listaCiudades[j]; // Guardamos la copia del objeto ordenado
//                    break;
//                }
//            }
//            actual = padres[actual]; // Retrocedemos al padre
//        }
//    }
//
//    // Liberamos la memoria de las estructuras auxiliares que usamos para calcular
//    delete[] distancias;
//    delete[] visitados;
//    delete[] padres;
//}
//
//// Copia secuencial de los datos ya calculados hacia el recipiente de la interfaz
//void Ruta::pasarCaminoAInterfaz(Ciudad arrayDestinoUI[]) {
//    for (int i = 0; i < cantidadCiudadesCamino; i++) {
//        arrayDestinoUI[i] = caminoOptimo[i];
//    }
//}
//
//int Ruta::obtenerDistanciaTotal() { return distanciaTotal; }
//int Ruta::obtenerCantidadCiudadesCamino() { return cantidadCiudadesCamino; }
