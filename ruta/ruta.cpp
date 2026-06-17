#include <ruta.h>
#include <climits>

Ruta::Ruta() {}

struct ResultadoRuta Ruta::encontrarRuta(int** matriz, int cantidadCiudades, int idOrigen, int idDestino){
    // 1. INICIALIZACIÓN
    int* distancias = new int[cantidadCiudades];
    bool* visitados = new bool[cantidadCiudades];
    int* padres = new int[cantidadCiudades];

    for (int i = 0; i < cantidadCiudades; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = false;
        padres[i] = -1;
    }

    distancias[idOrigen] = 0;

    // 2. BUCLE PRINCIPAL
    for (int cuenta = 0; cuenta < cantidadCiudades - 1; cuenta++) {

        // Buscar el nodo mínimo no visitado
        int minDistancia = INT_MAX;
        int u = -1;

        for (int v = 0; v < cantidadCiudades; v++) {
            if (!visitados[v] && distancias[v] <= minDistancia) {
                minDistancia = distancias[v];
                u = v;
            }
        }

        // REGLA 2: Si el nodo más cercano está a distancia "infinito",
        // significa que las ciudades restantes son completamente inaccesibles.
        if (u == -1 || distancias[u] == INT_MAX) {
            break;
        }

        if (u == idDestino) {
            break; // Ya encontramos el camino óptimo al destino, optimizamos tiempo
        }

        visitados[u] = true;

        // RELAJACIÓN DE ARISTAS
        for (int v = 0; v < cantidadCiudades; v++) {
            // REGLA 1 MODIFICADA:
            // Para que 'v' sea un vecino válido, la matriz NO puede tener -1 (sin conexión) ni 0 (sí mismo)
            if (!visitados[v] && matriz[u][v] != -1 && matriz[u][v] > 0) {

                // Evitamos sumar a un infinito (evita desborde de memoria)
                if (distancias[u] != INT_MAX) {
                    if (distancias[u] + matriz[u][v] < distancias[v]) {
                        distancias[v] = distancias[u] + matriz[u][v];
                        padres[v] = u;
                    }
                }
            }
        }
    }

    // 3. RECONSTRUCCIÓN Y SALIDA
    ResultadoRuta resultado;

    // REGLA 2: Si el destino quedó con distancia INFINITO, es inaccesible
    if (distancias[idDestino] == INT_MAX) {
        resultado.indices = nullptr;
		resultado.cantidadNodosRecorridos = 0;
        resultado.distancia = -1; // Señal de alerta para tu UI

        delete[] distancias;
        delete[] visitados;
        delete[] padres;

        return resultado;
    }

    // Contar nodos del camino
    int cuentaNodos = 0;
    int actual = idDestino;
    while (actual != -1) {
        cuentaNodos++;
        actual = padres[actual];
    }

    // Reservar memoria para el struct de respuesta
    resultado.indices = new int[cuentaNodos];
    resultado.cantidadNodosRecorridos = cuentaNodos;
    resultado.distancia = distancias[idDestino];

    // Cargar los índices al revés
    actual = idDestino;
    for (int i = cuentaNodos - 1; i >= 0; i--) {
        resultado.indices[i] = actual;
        actual = padres[actual];
    }

    // Liberar memoria temporal
    delete[] distancias;
    delete[] visitados;
    delete[] padres;

    return resultado;
}
