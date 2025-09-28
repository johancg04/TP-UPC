#include "ListaEnvios.h"
#include "Menu.h"
#include "Envio.h"
#include "Paquete.h"
#include "Sobre.h"

int main() {
	ListaEnvios lista;
	short opcion;

    //Caso de prueba paquete
    Paquete* p1 = new Paquete(1, 4.0, "20x5x100", "Lima", "Cusco", "Pendiente","Ropa", 200.0, true);
    lista.insertarInicio(p1);
    //Caso de prueba sobre
    Envio* s1 = new Sobre(1,0.5,"A4","Arequipa","Lima","Pendiente",25,true,true);
    lista.insertarInicio(s1);

	while (1) {
		//system("cls");
		mostrarMenu();
		cout << "Ingrese operacion: \n";
		cin >> opcion;

        if (opcion == 1) {
            int idEnvio;
            string tipo, dimensiones, origen, destino, estado;
            double peso;

            cout << "ID Envio: "; cin >> idEnvio;
            cout << "Tipo de envio (Paquete/Sobre): "; cin >> tipo;
            cout << "Peso: "; cin >> peso;
            cout << "Dimensiones: "; cin >> dimensiones;
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            cout << "Estado: "; cin >> estado;

            if (tipo == "Paquete") {
                string contenido;
                double valorDeclarado;
                bool asegurado;

                cout << "Contenido: "; cin >> contenido;
                cout << "Valor declarado: "; cin >> valorDeclarado;
                cout << "Asegurado? (1=Si, 0=No): "; cin >> asegurado;

                Envio* nuevo = new Paquete(idEnvio, peso, dimensiones, origen, destino, estado,
                    contenido, valorDeclarado, asegurado);

                lista.insertarInicio(nuevo);
                cout << "Paquete registrado con costo: " << nuevo->getCosto() << " soles\n";
            }
            else if (tipo == "Sobre") {
                int numeroHojas;
                bool urgente;
                bool clienteFrecuente;

                cout << "Número de hojas: "; cin >> numeroHojas;
                cout << "Es urgente? (1=Si, 0=No): "; cin >> urgente;
                cout << "Cliente frecuente? (1=Si, 0=No): "; cin >> clienteFrecuente;

                Envio* nuevo = new Sobre(idEnvio, peso, dimensiones, origen, destino, estado,
                    numeroHojas, urgente, clienteFrecuente);

                lista.insertarInicio(nuevo);
                cout << "Sobre registrado con costo: " << nuevo->getCosto() << " soles\n";
            }
            else {
                cout << "Tipo de envio no válido.\n";
            }
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