#include "funciones.h"
#include "head.h"

/*
Limpia la consola.
*/
void limpiarPantalla() {
	system("cls");
}

/*
Cambia el color actual de la consola.
*/
void cambiarColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*
Vuelve al color normal.
*/
void colorNormal() {
	cambiarColor(COLOR_NORMAL);
}

/*
Pausa el programa hasta presionar ENTER.
*/
void pausar() {
	cout << "\nPresione ENTER para continuar...";
	cin.ignore(10000, '\n');
	cin.get();
}

/*
Muestra la lista de ciudades disponibles.
*/
void mostrarCiudades() {
	cout << "===== CIUDADES =====\n\n";
	cout << "A = Perito Moreno\n";
	cout << "B = Puerto Deseado\n";
	cout << "C = Gregores\n";
	cout << "D = Puerto Santa Cruz\n";
	cout << "E = El Calafate\n";
}

/*
Convierte la letra de ciudad en un nombre completo.
*/
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

/*
Verifica si una letra corresponde a una ciudad valida.
*/
bool letraCiudadValida(char letra) {
	letra = toupper(letra);
	return letra >= 'A' && letra <= 'E';
}

/*
Determina si un caracter es una ciudad.
*/
bool esCiudad(char valor) {
	return valor >= 'A' && valor <= 'E';
}

/*
===============================================================================
						INICIALIZACION DEL MAPA
===============================================================================
*/

/*
Inicializa TODO el mapa como bloqueado ('0').
*/
void inicializarMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]) {
	for (int y = 0; y < FILAS_MAPA; y++) {
		for (int x = 0; x < COLUMNAS_MAPA; x++) {
			mapa[y][x] = BLOQUEADO;
		}
	}
}

/*
Carga manualmente las avenidas transitables.

Las posiciones marcadas con '1' son caminos posibles.
*/
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

/*
Coloca las ciudades dentro del mapa.
*/
void cargarCiudadesEnMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]) {

	mapa[1][1] = 'A';
	mapa[1][8] = 'B';
	mapa[5][4] = 'C';
	mapa[7][8] = 'D';
	mapa[8][2] = 'E';
}

/*
Construye completamente el mapa:
1) Inicializa
2) Agrega avenidas
3) Agrega ciudades
*/
void cargarMapa(char mapa[FILAS_MAPA][COLUMNAS_MAPA]) {
	inicializarMapa(mapa);
	cargarAvenidasEnMapa(mapa);
	cargarCiudadesEnMapa(mapa);
}

/*
Busca la coordenada exacta de una ciudad dentro del mapa.

Si la encuentra:
- guarda posicion
- retorna true
*/
bool buscarCoordenadaCiudad(char mapa[FILAS_MAPA][COLUMNAS_MAPA], char ciudad, Punto &posicion) {

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

/*
Verifica que una coordenada no se salga del mapa.
*/
bool estaDentroDelMapa(int y, int x) {
	return y >= 0 && y < FILAS_MAPA && x >= 0 && x < COLUMNAS_MAPA;
}

/*
Una casilla es transitable si:
- es avenida
- o es ciudad
*/
bool esTransitable(char valor) {
	return valor == AVENIDA || esCiudad(valor);
}

/*
Compara dos puntos.
*/
bool puntoIgual(Punto a, Punto b) {
	return a.y == b.y && a.x == b.x;
}

/*
Verifica si una coordenada ya pertenece a un camino.
*/
bool puntoEnCamino(Camino camino, int y, int x) {

	for (int i = 0; i < camino.tam; i++) {

		if (camino.puntos[i].y == y &&
			camino.puntos[i].x == x) {

			return true;
		}
	}

	return false;
}

/*
Verifica si un punto aparece en algun camino alternativo.

Se usa para pintar caminos secundarios en azul.
*/
bool puntoEnAlgunaAlternativa(Camino caminos[MAX_CAMINOS], int cantidad, int seleccionado, int y, int x) {

	for (int i = 0; i < cantidad; i++) {

		if (i != seleccionado &&
			puntoEnCamino(caminos[i], y, x)) {

			return true;
		}
	}

	return false;
}

/*
Guarda un camino encontrado dentro del arreglo de caminos.
*/
void guardarCamino(Camino caminos[MAX_CAMINOS], int &cantidad, Camino actual) {

	if (cantidad >= MAX_CAMINOS) {
		return;
	}

	caminos[cantidad] = actual;
	cantidad++;
}

/*
===============================================================================
						ALGORITMO DFS (Depth First Search)
===============================================================================

Este es el algoritmo mas importante del programa.

OBJETIVO:
Encontrar TODOS los caminos posibles entre dos ciudades.

FUNCIONAMIENTO:
- Recorre el mapa recursivamente.
- Va probando caminos posibles.
- Marca casillas visitadas para no repetir.
- Cuando llega al destino:
	=> guarda el camino.
- Luego retrocede (backtracking) para probar otras rutas.

MOVIMIENTOS:
- arriba
- derecha
- abajo
- izquierda

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

	/*
	Condicion de corte:
	- demasiados caminos
	- camino demasiado largo
	*/
	if (cantidadCaminos >= MAX_CAMINOS ||
		caminoActual.tam >= MAX_CASILLAS) {

		return;
	}

	/*
	Agrega el punto actual al camino.
	*/
	caminoActual.puntos[caminoActual.tam++] = actual;

	/*
	Marca la casilla como visitada.
	*/
	visitado[actual.y][actual.x] = 1;

	/*
	Si llegamos al destino:
	=> guardar camino completo.
	*/
	if (puntoIgual(actual, destino)) {

		guardarCamino(caminos, cantidadCaminos, caminoActual);

	} else {

		/*
		Vectores de movimiento.

		i=0 => arriba
		i=1 => derecha
		i=2 => abajo
		i=3 => izquierda
		*/
		int dy[4] = {-1, 0, 1, 0};
		int dx[4] = {0, 1, 0, -1};

		/*
		Prueba las 4 direcciones posibles.
		*/
		for (int i = 0; i < 4; i++) {

			int nuevoY = actual.y + dy[i];
			int nuevoX = actual.x + dx[i];

			/*
			Solo avanza si:
			- esta dentro del mapa
			- no fue visitado
			- es transitable
			*/
			if (estaDentroDelMapa(nuevoY, nuevoX) &&
				visitado[nuevoY][nuevoX] == 0 &&
				esTransitable(mapa[nuevoY][nuevoX])) {

				Punto siguiente;
				siguiente.y = nuevoY;
				siguiente.x = nuevoX;

				/*
				Llamada recursiva:
				continua explorando desde la nueva casilla.
				*/
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

	/*
	Backtracking:

	Al volver de la recursion:
	- desmarca visitado
	- elimina el punto actual

	Esto permite explorar otros caminos alternativos.
	*/
	visitado[actual.y][actual.x] = 0;
	caminoActual.tam--;
}

/*
Ordena los caminos encontrados desde el mas corto al mas largo.
*/
void ordenarCaminosPorDistancia(Camino caminos[MAX_CAMINOS], int cantidad) {

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

/*
Cantidad de casillas recorridas.
*/
int calcularCasillasRecorridas(Camino camino) {
	return camino.tam - 1;
}

/*
Convierte casillas en kilometros.
*/
int calcularKilometros(Camino camino) {
	return calcularCasillasRecorridas(camino) * KM_POR_CASILLA;
}

/*
Calcula tiempo estimado de viaje.
*/
int calcularHoras(Camino camino) {
	return calcularKilometros(camino) / VELOCIDAD_KM_H;
}

/*
===============================================================================
							MOSTRAR MAPA VISUAL
===============================================================================

Esta parte se encarga SOLO de dibujar el mapa.

Dependiendo del tipo de celda:
- cambia colores
- pinta caminos
- pinta ciudades
- pinta caminos alternativos

===============================================================================
*/

void mostrarCelda(char mapa[FILAS_MAPA][COLUMNAS_MAPA], Camino caminos[MAX_CAMINOS], int cantidadCaminos, int seleccionado, int y, int x) {

	char valor = mapa[y][x];

	if (esCiudad(valor)) {

		cambiarColor(COLOR_CIUDAD);

	} else if (seleccionado >= 0 &&
			   puntoEnCamino(caminos[seleccionado], y, x)) {

		cambiarColor(COLOR_CAMINO_SELECCIONADO);

	} else if (puntoEnAlgunaAlternativa(caminos, cantidadCaminos, seleccionado, y, x)) {

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

/*
Dibuja el mapa completo con coordenadas.
*/
void mostrarMapaVisual(char mapa[FILAS_MAPA][COLUMNAS_MAPA], Camino caminos[MAX_CAMINOS], int cantidadCaminos, int seleccionado) {

	cout << "Coordenadas: mapa[y][x]\n";

	cout << "Ciudades = rojo | No caminos = amarillo | Caminos = verde | Camino seleccionado = celeste | Caminos posibles = azul\n";

	cout << "\n     ";

	for (int x = 0; x < COLUMNAS_MAPA; x++) {
		cout << setw(2) << x << ' ';
	}

	cout << endl;

	for (int y = 0; y < FILAS_MAPA; y++) {

		cout << setw(3) << y << "  ";

		for (int x = 0; x < COLUMNAS_MAPA; x++) {

			mostrarCelda(mapa, caminos, cantidadCaminos, seleccionado, y, x);
		}

		cout << endl;
	}
}

/*
Muestra el mapa sin caminos seleccionados.
*/
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
Muestra informacion resumida del camino.
*/
void mostrarResumenCamino(Camino camino, char origen, char destino) {

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

/*
Muestra todos los caminos encontrados.
*/
void mostrarOpcionesDeCamino(Camino caminos[MAX_CAMINOS], int cantidadCaminos) {

	cout << "===== CAMINOS ENCONTRADOS =====\n\n";

	for (int i = 0; i < cantidadCaminos; i++) {

		cout << i + 1 << " = Camino " << i + 1;

		if (i == 0) {
			cout << "*";
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
					MENU DE CAMINOS ENCONTRADOS
===============================================================================

Permite:
- cambiar entre caminos
- visualizar alternativas
- ver resumen de distancia y tiempo

===============================================================================
*/

void menuCaminosEncontrados(char mapa[FILAS_MAPA][COLUMNAS_MAPA],
							Camino caminos[MAX_CAMINOS],
							int cantidadCaminos,
							char origen,
							char destino) {

	char opcion;
	int seleccionado = 0;

	do {

		limpiarPantalla();

		mostrarCiudades();

		cout << "\n";

		mostrarMapaVisual(mapa, caminos, cantidadCaminos, seleccionado);

		cout << "\nCamino mostrado actualmente: "
			 << seleccionado + 1
			 << "\n\n";

		mostrarResumenCamino(caminos[seleccionado], origen, destino);

		cout << "\n";

		mostrarOpcionesDeCamino(caminos, cantidadCaminos);

		cout << "\n>> ";

		cin >> opcion;

		opcion = toupper(opcion);

		/*
		Si el usuario ingresa un numero:
		se cambia el camino seleccionado.
		*/
		if (opcion >= '1' && opcion <= '9') {

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

FLUJO GENERAL:

1) cargar mapa
2) pedir origen y destino
3) validar datos
4) buscar coordenadas
5) ejecutar DFS
6) ordenar caminos
7) mostrar resultados

===============================================================================
*/

void buscarConexion() {

	char mapa[FILAS_MAPA][COLUMNAS_MAPA];

	Camino caminos[MAX_CAMINOS];
	Camino caminoActual;

	int visitado[FILAS_MAPA][COLUMNAS_MAPA];

	int cantidadCaminos = 0;

	char origenLetra, destinoLetra;

	Punto origen, destino;

	cargarMapa(mapa);

	caminoActual.tam = 0;

	/*
	Inicializa matriz de visitados.
	*/
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

	/*
	Validaciones de entrada.
	*/
	if (!letraCiudadValida(origenLetra) ||
		!letraCiudadValida(destinoLetra)) {

		cout << "\nERROR: Ciudad invalida.\n";
		cout << "Solo puede ingresar letras entre A y E.\n";
		return;
	}

	if (origenLetra == destinoLetra) {

		cout << "\nERROR: El origen y el destino no pueden ser la misma ciudad.\n";
		return;
	}

	/*
	Busca coordenadas reales de las ciudades.
	*/
	if (!buscarCoordenadaCiudad(mapa, origenLetra, origen) ||
		!buscarCoordenadaCiudad(mapa, destinoLetra, destino)) {

		cout << "\nERROR: No se encontro alguna ciudad en el mapa.\n";
		return;
	}

	/*
	Ejecuta DFS para encontrar caminos.
	*/
	buscarCaminosDFS(
					  mapa,
					  origen,
					  destino,
					  visitado,
					  caminoActual,
					  caminos,
					  cantidadCaminos
					  );

	/*
	Ordena desde el mas corto al mas largo.
	*/
	ordenarCaminosPorDistancia(caminos, cantidadCaminos);

	/*
	Si no hay caminos posibles.
	*/
	if (cantidadCaminos == 0) {

		cout << "\nNo existe camino entre esas ciudades usando las avenidas del mapa.\n\n";

		mostrarMapaVisual(mapa, caminos, 0, -1);

		return;
	}

	/*
	Muestra menu de caminos encontrados.
	*/
	menuCaminosEncontrados(
							mapa,
							caminos,
							cantidadCaminos,
							origenLetra,
							destinoLetra
							);
}

/*
Menu principal del programa.
*/
void mostrarMenu() {

	cout << "===== MENU PRINCIPAL =====\n\n";

	cout << "0 = Ver mapa\n";
	cout << "1 = Elegir viaje\n";
	cout << "X = Finalizar\n\n";

	cout << "Ingrese una opcion: ";
}
