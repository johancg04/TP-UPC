#include "ListaEnvios.h"
#include "Menu.h"
#include "Envio.h"

int main() {
	ListaEnvios lista;
	short opcion;

    //SOLO PARA PRUEBAS
    Envio* e1 = new Envio(1, "Paquete", 4.0, "30x20x10", "Lima", "Cusco", "Pendiente");
    Envio* e2 = new Envio(2, "Sobre", 0.5, "A4", "Arequipa", "Lima", "Entregado");
    Envio* e3 = new Envio(3, "Paquete", 2.5, "25x15x10", "Piura", "Trujillo", "En transito");
    Envio* e4 = new Envio(4, "Sobre", 0.2, "Carta", "Chiclayo", "Tacna", "Pendiente");
    Envio* e5 = new Envio(5, "Caja", 3.0, "40x30x20", "Puno", "Ica", "Pendiente");
    lista.insertarInicio(e1);
    lista.insertarInicio(e2);
    lista.insertarInicio(e3);
    lista.insertarInicio(e4);
    lista.insertarInicio(e5);

	while (1) {
		//system("cls");
		mostrarMenu();
		cout << "Ingrese operacion: \n";
		cin >> opcion;

        if (opcion == 1) {
            /*Envio* nuevo = new Envio();

            int idEnvio;
            string tipo, dimensiones, origen, destino, estado;
            double peso;

            cout << "ID Envio: "; cin >> idEnvio;
            nuevo->setId(idEnvio);

            cout << "Tipo de envio(Paquete/Sobre): "; cin >> tipo;
            nuevo->setTipo(tipo);

            cout << "Peso: "; cin >> peso;
            nuevo->setPeso(peso);

            cout << "Dimensiones: "; cin >> dimensiones;
            nuevo->setDimensiones(dimensiones);

            cout << "Origen: "; cin >> origen;
            nuevo->setOrigen(origen);

            cout << "Destino: "; cin >> destino;
            nuevo->setDestino(destino);

            cout << "Estado: "; cin >> estado;
            nuevo->setEstado(estado);

            nuevo->calcularCosto();

            lista.insertarInicio(nuevo);
            nuevo->registrarEnvio();
            cout << "Costo calculado: " << nuevo->getCosto() << " soles\n";*/
        }

        if (opcion == 2) {
            cout << "\nBusqueda por ID\n";
            int idBuscar;
            cout << "Ingrese ID: ";
            cin >> idBuscar;

            Envio* envioBuscado = lista.buscarEnvioPorId(idBuscar);

            if (envioBuscado != nullptr) {
                cout << "----------- Envio encontrado -----------\n";
                envioBuscado->mostrar();
            }
            else {
                cout << "No se encontro el envio\n";
            }
        }
        if (opcion == 3) {
            int idEliminar;
            cout << "Ingrese el ID a eliminar: ";
            cin >> idEliminar;
            lista.eliminarPorId(idEliminar);
        }
        if (opcion == 4) {
            int idActualizar;
            string nuevoEstado;

            cout << "Ingrese ID del envio a actualizar: ";
            cin >> idActualizar;

            Envio* envioBuscado = lista.buscarEnvioPorId(idActualizar);

            if (envioBuscado != nullptr) {
                cout << "Ingrese el nuevo estado (Pendiente/En transito/Entregado): ";
                cin.ignore();
                getline(cin, nuevoEstado);

                envioBuscado->actualizarEstado(nuevoEstado);
            }
            else {
                cout << "Envio con ID " << idActualizar << " no encontrado.\n";
            }
        }
		if (opcion == 5) {
			lista.mostrarLista();
		}
	}

    system("pause>0");
    return 0;
}