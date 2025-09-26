#include "ListaEnvios.h"
#include "Menu.h"
#include "Envio.h"

int main() {
	ListaEnvios lista;
	short opcion;

	while (1) {
		//system("cls");
		mostrarMenu();
		cout << "Ingrese operacion: \n";
		cin >> opcion;

		if (opcion == 1) {
			Envio* e = new Envio();
			e->registrarEnvio();
			lista.insertar(e);
		}
		if (opcion == 2) {
			cout << "=== LISTA DE ENVIOS ===" << endl;
			lista.mostrar();
		}
	}

	system("pause>0");
	return 0;
}