# Informe Técnico — Sistema Inteligente de Logística

**Gestión Logística · Provincia de Santa Cruz**  
Estructuras de Datos y Algoritmos II · UPE 2026

---

## Índice

1. [Descripción general](#1-descripción-general)
2. [Arquitectura del sistema](#2-arquitectura-del-sistema)
3. [Estructuras de datos](#3-estructuras-de-datos)
4. [Clases principales](#4-clases-principales)
5. [Algoritmo de Dijkstra](#5-algoritmo-de-dijkstra)
6. [Persistencia de datos](#6-persistencia-de-datos)
7. [Interfaz gráfica](#7-interfaz-gráfica)

---

## 1. Descripción general

El sistema modela la red logística de la Provincia de Santa Cruz como un grafo no dirigido con pesos. Cada ciudad es un nodo y cada ruta entre ciudades es una arista con un peso que representa la distancia en kilómetros. Sobre ese grafo se aplica el algoritmo de Dijkstra para encontrar el camino de menor costo entre dos nodos dados.

La aplicación está desarrollada en C++ usando VCL (Visual Component Library) de Embarcadero RAD Studio para la interfaz gráfica. La lógica del negocio está separada de la interfaz mediante clases independientes: `Ciudad`, `Mapa` y `Ruta`. La interfaz actúa como capa de presentación que consume los datos que le pasan esas clases, sin conocer su implementación interna.

---

## 2. Arquitectura del sistema

El proyecto sigue una separación de responsabilidades por entidad. Cada clase se encarga de su propio dominio y la interfaz gráfica no sabe nada de cómo funcionan por dentro.

```
ciudad/     → clase Ciudad
mapa/       → clase Mapa
ruta/       → clase Ruta
archivos/   → ciudades.dat · matriz.dat · historial.dat
InterfazLogistica.cpp/.h/.dfm  → capa de presentación VCL
GestionLogistica.cpp            → punto de entrada (WinMain)
structs.h                       → estructuras compartidas
```

El flujo de datos es el siguiente: al iniciar la aplicación, `Mapa` lee los archivos `.dat` y construye en memoria la lista de ciudades y la matriz de adyacencia. La interfaz le pide esos datos a `Mapa` a través de sus getters y los usa para renderizar el mapa y poblar las tablas. Cuando el usuario solicita calcular una ruta, la interfaz llama a `Ruta` pasándole el mapa, y `Ruta` ejecuta Dijkstra sobre la matriz devolviendo un `ResultadoRuta`.

Un punto clave del diseño es que **el único dueño real de los datos es `Mapa`**. La interfaz trabaja con una copia local (`ciudadesUI`) que se llena a través de `pasarListaCiudades()`. Cualquier cambio en la red tiene que pasar por `Mapa` primero, y la interfaz se actualiza leyendo de él de nuevo.

---

## 3. Estructuras de datos

### Grafo de adyacencia

La red logística se representa como una **matriz de adyacencia dinámica de `n x n`**, donde `n` es la cantidad de ciudades cargadas desde el archivo. Cada celda `[i][j]` contiene la distancia en kilómetros entre la ciudad `i` y la ciudad `j`. Un valor de `0` indica que no hay conexión directa.

La matriz se asigna dinámicamente en el constructor de `Mapa`. El tamaño no está hardcodeado: se determina contando las líneas del archivo `matriz.dat` antes de reservar memoria, lo que permite que el sistema escale si se agregan ciudades.

```cpp
matrizAdyacencia = new int*[cantidadCiudades];
for (int i = 0; i < cantidadCiudades; i++) {
    matrizAdyacencia[i] = new int[cantidadCiudades];
}
```

El destructor libera toda esa memoria explícitamente para evitar leaks:

```cpp
for (int i = 0; i < cantidadCiudades; i++) {
    delete[] matrizAdyacencia[i];
}
delete[] matrizAdyacencia;
```

### Coordenadas

```cpp
struct Coordenadas {
    int x;
    int y;
};
```

Representa la posición de cada ciudad en el canvas del mapa. Los valores son píxeles sobre la imagen de la provincia y se usan para pintar los nodos en su posición geográfica aproximada.

### ResultadoRuta

```cpp
struct ResultadoRuta {
    int cantidadNodosRecorridos;
    int* indices;
    int distancia;
};
```

Es el objeto que devuelve el algoritmo de Dijkstra con el camino calculado: la cantidad de nodos que forman el camino, el array de índices de esos nodos en orden, y la distancia total en kilómetros.

---

## 4. Clases principales

### Ciudad

Representa un nodo del grafo. Encapsula el ID, el nombre, las coordenadas en el mapa y un flag `activa` que permite desactivar una ciudad sin eliminarla físicamente de la memoria. Esto es importante porque la matriz de adyacencia usa los IDs como índices: si se eliminara una ciudad del medio, los índices de todas las demás cambiarían y la matriz quedaría inconsistente.

| Método | Descripción |
|---|---|
| `obtenerNombre()` | Devuelve el nombre de la ciudad |
| `obtenerId()` | Devuelve el ID numérico |
| `obtenerCoordenadas()` | Devuelve las coordenadas X, Y |
| `obtenerEstado()` | Devuelve si la ciudad está activa |
| `cambiarEstado()` | Alterna el estado activo/inactivo |

### Mapa

Es la clase central del sistema. En su constructor lee los archivos `.dat`, construye la matriz de adyacencia y la lista de ciudades en memoria. Provee getters para que la interfaz y `Ruta` accedan a los datos sin modificarlos directamente.

El constructor hace dos lecturas del archivo `matriz.dat`: la primera para contar líneas y determinar `n`, y la segunda (después de un `seekg` al inicio) para leer los valores. Entre las dos se llama a `matriz.clear()` para limpiar el flag de EOF que queda al llegar al final del archivo en la primera pasada.

Para leer los valores de la matriz usa el operador `>>` de `stringstream`, que tiene la propiedad de saltearse automáticamente espacios en blanco y tabulaciones, lo que hace que el formato del archivo sea flexible.

| Método | Descripción |
|---|---|
| `obtenerCantidadCiudades()` | Devuelve la cantidad de ciudades cargadas |
| `obtenerMatrizAdyacencia()` | Devuelve el puntero a la matriz dinámica |
| `pasarListaCiudades(array[])` | Copia las ciudades activas al array de destino |
| `actualizarCantidadCiudades(int)` | Suma o resta al contador de ciudades |
| `agregarCiudad()` | Agrega una nueva ciudad al sistema |
| `eliminarCiudad(int id)` | Elimina una ciudad por ID |

### Ruta

Recibe un puntero al `Mapa` en su constructor y expone `encontrarRuta()` que ejecuta Dijkstra sobre la matriz de adyacencia.

| Método | Descripción |
|---|---|
| `encontrarRuta(matriz, n, origen, destino)` | Ejecuta Dijkstra y devuelve un `ResultadoRuta` |

---

## 5. Algoritmo de Dijkstra

El algoritmo se aplica sobre la matriz de adyacencia dinámica. Recibe la matriz, la cantidad de ciudades, el ID de origen y el ID de destino, y devuelve el camino de menor costo.

**Arrays auxiliares utilizados:**

- `distancias[]` — se inicializa con `2.000.000.000` (valor que simula infinito) para todos los nodos excepto el origen, que arranca en `0`.
- `visitados[]` — flags booleanos, todos en `false` al inicio.
- `padres[]` — se inicializa en `-1` para todos. Guarda desde qué nodo se llegó a cada uno, lo que permite reconstruir el camino al final recorriendo este array hacia atrás.

**Pasos del algoritmo:**

1. Inicializar los tres arrays auxiliares como se describió arriba.
2. En cada iteración, buscar el nodo no visitado con menor distancia acumulada. Solo se evalúan ciudades con `obtenerEstado() == true`.
3. Marcar ese nodo como visitado. Si es el destino, terminar.
4. Para cada vecino del nodo actual: si está activo, no fue visitado, hay conexión directa en la matriz (valor distinto de `-1`) y la distancia acumulada más el peso de la arista mejora la distancia conocida del vecino, actualizar.
5. Una vez que el destino es procesado, recorrer `padres[]` desde el destino hacia el origen para reconstruir el camino. Primero se cuenta cuántos nodos lo componen, luego se reserva el array dinámico con ese tamaño exacto y se llena al revés.

**Complejidad:** O(n²) con matriz de adyacencia y búsqueda lineal del mínimo, donde `n` es la cantidad de ciudades.

**Manejo de rutas inexistentes:** si al finalizar la distancia al destino sigue siendo `2.000.000.000`, significa que no hay camino posible entre los nodos dados y `distanciaTotal` queda en `-1`.

---

## 6. Persistencia de datos

Los datos del sistema se leen y escriben en tres archivos de texto plano dentro de la carpeta `archivos/`. Esta carpeta tiene que estar en el mismo directorio que el ejecutable.

### ciudades.dat

Una ciudad por línea, campos separados por `;`:

```
0;El Calafate;288;428
1;Gdor. Gregores;400;260
2;Pto. San Julian;552;325
3;Corpen;448;347
4;Alke Guer;440;532
5;Gendarme Barreto;368;430
6;Pico Truncado;504;112
7;Cte. Luis Piedrabuena;520;387
```

El constructor de `Mapa` usa `std::getline` con `;` como delimitador para extraer cada campo como string y luego los convierte con `std::stoi`.

### matriz.dat

La matriz de adyacencia completa. Cada línea es una fila, valores separados por espacios o tabulaciones. Un `0` indica que no hay conexión directa entre esas dos ciudades. La cantidad de líneas determina `n` dinámicamente, así que agregar una ciudad implica agregar una fila y una columna a este archivo.

### historial.dat

Almacena el registro de las rutas calculadas durante la sesión. Se escribe cuando el usuario presiona **Guardar Historial** desde la interfaz.

---

## 7. Interfaz gráfica

La interfaz está construida con VCL sobre un único formulario (`TForm1`) que gestiona todos los paneles internamente. La navegación entre secciones se hace mostrando y ocultando paneles (`Visible = true/false`) sin cambiar de ventana.

### Inicialización

Al construirse el formulario, `TForm1` instancia `Mapa`, obtiene la matriz de adyacencia y la copia de ciudades, y arma los combos de origen y destino. Después crea el `TPaintBox` del mapa en tiempo de ejecución y lo superpone al panel con `BringToFront()`. Los punteros de los campos de texto de la vista Ciudades (`txtCiudadId`, `txtCiudadNombre`, etc.) se inicializan en `nullptr` porque esa vista se construye dinámicamente solo cuando el usuario la abre.

### Renderizado del mapa

El mapa se dibuja en el evento `OnPaint` del `TPaintBox`. La función `pintarCiudades()` hace dos pasadas sobre los datos:

**Primera pasada — líneas de conexión:** recorre la matriz de adyacencia con `j = i + 1` para evitar procesar la diagonal y no dibujar rutas duplicadas. Solo dibuja si ambas ciudades están activas y el valor en la matriz es distinto de `0` y de `-1`.

**Segunda pasada — nodos:** dibuja el círculo azul de cada ciudad activa en sus coordenadas, el ID adentro en blanco y el nombre al costado en azul.

### Construcción dinámica de vistas

Las vistas de Ciudades y Rutas no existen en el `.dfm`: se construyen completamente en C++ cada vez que el usuario navega a esa sección. `construirVistaCiudades()` y `construirVistaRutas()` primero limpian todos los controles del panel con un loop sobre `ControlCount`, y luego crean `TLabel`, `TStringGrid`, `TEdit` y `TPanel` dinámicamente. Esto garantiza que la vista siempre refleje el estado actual en memoria.

El `TStringGrid` de ciudades tiene el dibujado personalizado desactivado (`DefaultDrawing = false`) y usa el evento `OnDrawCell` para renderizar cada celda manualmente, incluyendo el resaltado de la fila seleccionada. Al seleccionar una fila se dispara `OnSelectCell`, que llama a `actualizarCamposCiudad()` para cargar los datos de esa ciudad en los campos de texto del panel lateral.