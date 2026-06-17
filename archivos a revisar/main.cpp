#include "head.h"
#include "funciones.h"


/*
===============================================================================
									MAIN
===============================================================================

FLUJO PRINCIPAL DEL PROGRAMA:

while:
	- mostrar menu
	- leer opcion
	- ejecutar accion

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