# tp_eda2 — Gestión Logística · Provincia de Santa Cruz

## Sobre el Proyecto

Gestión Logística es una aplicación de escritorio desarrollada en C++ con interfaz VCL que modela la red de rutas y ciudades de la Provincia de Santa Cruz mediante Teoría de Grafos. El sistema permite calcular caminos óptimos entre puntos logísticos, gestionar la red de ciudades y simular cortes de ruta en tiempo real.

Proyecto Final > Asignatura: Estructuras de Datos y Algoritmos II > Universidad Provincial de Ezeiza (UPE) — Tecnicatura Universitaria en Desarrollo de Software.

## Integrantes

- Fajardo Lopez, Yeison Andrés — [GitHub](https://github.com/Yeisonfjrd)
- Gomez, Matías Ezequiel — [GitHub](https://github.com/M4T1A2v)
- Martin, Maximiliano Sebastián — [GitHub](https://github.com/Nirbeat)
- Zarza Báez, Lucía Esmeralda — [GitHub](https://github.com/ZarzaLucia)

## Características

- **Gestión de ciudades:** listado, visualización y administración de los nodos de la red logística.
- **Matriz de adyacencia:** representa las conexiones y distancias entre ciudades, cargada desde archivos `.dat`.
- **Optimización de rutas (Dijkstra):** calcula el camino más corto entre dos ciudades sobre el grafo.
- **Gestión de contingencias:** permite marcar rutas como cortadas y recalcular trayectorias alternativas.
- **Historial:** registro de las rutas calculadas durante la sesión.
- **Interfaz gráfica:** mapa visual de la provincia con ciudades y conexiones renderizadas en tiempo real.

## Estado actual

| Módulo | Estado |
|---|---|
| Carga de ciudades desde archivo | listo |
| Matriz de adyacencia | listo |
| Pintado de ciudades y conexiones | listo |
| Vista de gestión de ciudades | listo |
| Vista de gestión de rutas | listo |
| Dijkstra | en desarrollo |
| Agregar / eliminar ciudades | en desarrollo |
| Historial de rutas | en desarrollo |
| Corte de rutas | en desarrollo |

## Estructura

```
ciudad/    → clase Ciudad (id, nombre, coordenadas, estado activo)
mapa/      → clase Mapa (matriz de adyacencia, lista de ciudades)
ruta/      → clase Ruta (algoritmo de búsqueda de camino óptimo)
archivos/  → ciudades.dat · matriz.dat · historial.dat
```

## Documentación

- [Manual de Usuario](./docs/Manual.md)
- [Informe Técnico](./docs/InformeTecnico.md)

## Requisitos

- Windows
- C++ Builder / Embarcadero RAD Studio para compilar

## Cómo ejecutarlo

Abrir `GestionLogistica.cbproj` en C++ Builder y compilar el proyecto.