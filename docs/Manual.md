# Manual de Usuario — Sistema Inteligente de Logística

**Gestión Logística · Provincia de Santa Cruz**  
Estructuras de Datos y Algoritmos II · UPE 2026

---

## Índice

1. [Introducción](#1-introducción)
2. [Requisitos e instalación](#2-requisitos-e-instalación)
3. [Guía de interfaz](#3-guía-de-interfaz)
4. [Guía de uso](#4-guía-de-uso)

---

## 1. Introducción

El Sistema Inteligente de Logística es una aplicación de escritorio desarrollada en C++ con interfaz gráfica VCL. Modela la red de ciudades y rutas de la Provincia de Santa Cruz como un grafo de adyacencia, permitiendo calcular caminos óptimos entre puntos logísticos y gestionar la red en tiempo real.

El operador puede ver el mapa de la provincia con las ciudades y conexiones dibujadas, elegir origen y destino, calcular la ruta más corta y gestionar el alta y baja de ciudades y rutas desde la misma interfaz.

---

## 2. Requisitos e instalación

**Requisitos del sistema**

- Sistema Operativo: Windows 10 u 11 (64 bits)
- Resolución de pantalla: mínimo 1280x720 píxeles
- C++ Builder / Embarcadero RAD Studio para compilar desde código fuente

**Instalación y ejecución**

1. Clonar el repositorio y pararse en la rama `limpio`
2. Abrir el archivo `GestionLogistica.cbproj` en C++ Builder
3. Compilar el proyecto en configuración Win32/Debug
4. Ejecutar el binario generado en `Win32/Debug/GestionLogistica.exe`

> La carpeta `archivos/` tiene que estar en el mismo directorio que el ejecutable. Ahí están los archivos `ciudades.dat`, `matriz.dat` e `historial.dat` que el programa lee al iniciar. Si se mueve el `.exe` sin esa carpeta, no va a cargar ningún dato.

---

## 3. Guía de interfaz

Al abrir el programa se muestra directamente la pantalla principal con el mapa de Santa Cruz. La interfaz tiene dos zonas: el menú lateral izquierdo para navegar entre secciones, y el área de contenido que cambia según lo que se seleccione.

### 3.1 Menú lateral

El sidebar tiene cuatro opciones:

- **Calcular Ruta** — pantalla principal con el mapa y los selectores de origen y destino
- **Ciudades** — gestión del listado de ciudades cargadas en el sistema
- **Rutas** — listado de todas las conexiones entre ciudades con sus distancias
- **Historial** — registro de rutas calculadas

### 3.2 Pantalla principal — Cálculo de ruta

![Pantalla principal](./assets/img_calcular.png)

Es la pantalla que aparece al abrir el programa. A la izquierda hay un panel con dos listas desplegables para elegir la ciudad de origen y la ciudad de destino, más tres botones:

- **Calcular Ruta Óptima** — dispara el algoritmo de Dijkstra sobre la matriz de adyacencia y muestra el resultado
- **Guardar Historial** — guarda el resultado del cálculo actual en el archivo `historial.dat`
- **Limpiar Campos** — resetea los selectores a sus valores por defecto

A la derecha se muestra el mapa de la provincia con los nodos dibujados como círculos azules con su ID y nombre, y las conexiones como líneas grises entre ellos. Las ciudades actualmente cargadas son:

| ID | Ciudad |
|---|---|
| 0 | El Calafate |
| 1 | Gdor. Gregores |
| 2 | Pto. San Julian |
| 3 | Corpen |
| 4 | Alke Guer |
| 5 | Gendarme Barreto |
| 6 | Pico Truncado |
| 7 | Cte. Luis Piedrabuena |

### 3.3 Gestión de Ciudades

![Gestión de ciudades](./assets/img_ciudades.png)

Se accede desde el menú lateral haciendo clic en **Ciudades**. Tiene tres paneles:

- **Listado de Ciudades** — tabla con el ID, nombre y coordenadas (X, Y) de cada ciudad. Al hacer clic en una fila, los datos se cargan automáticamente en el panel de la derecha
- **Datos de la Ciudad** — muestra el ID, nombre y coordenadas de la ciudad seleccionada
- **Acciones** — botón para agregar una nueva ciudad y botón para eliminar la seleccionada

### 3.4 Gestión de Rutas

![Gestión de rutas](./assets/img_rutas.png)

Se accede desde el menú lateral haciendo clic en **Rutas**. Muestra todas las conexiones existentes en la red: ciudad de origen, ciudad de destino y distancia en kilómetros. A la derecha están los botones para agregar una nueva ruta o eliminar la seleccionada.

---

## 4. Guía de uso

### Calcular la ruta óptima entre dos ciudades

1. Ir a la sección **Calcular Ruta** desde el menú lateral
2. Seleccionar la ciudad de origen en el primer desplegable
3. Seleccionar la ciudad de destino en el segundo desplegable
4. Presionar **Calcular Ruta Óptima**
5. El sistema procesa la matriz de adyacencia con Dijkstra y devuelve el camino de menor distancia total en kilómetros

Para guardar el resultado, presionar **Guardar Historial** antes de cambiar los campos. Para resetear la selección, usar **Limpiar Campos**.

### Consultar el listado de ciudades

Desde la sección **Ciudades** se puede ver toda la información de los nodos cargados. Haciendo clic en cualquier fila de la tabla, los datos de esa ciudad se cargan en el panel lateral derecho.

### Consultar el listado de rutas

Desde la sección **Rutas** se pueden ver todas las conexiones activas entre ciudades con la distancia en kilómetros de cada tramo. El listado se genera directamente desde la matriz de adyacencia en memoria.

### Consultar el historial

La sección **Historial** muestra las rutas calculadas que se guardaron durante la sesión. Los registros se almacenan en el archivo `historial.dat` dentro de la carpeta `archivos/`.