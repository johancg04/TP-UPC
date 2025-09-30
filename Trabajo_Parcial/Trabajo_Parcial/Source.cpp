#include "ListaEnvios.h"
#include "Menu.h"
#include "Envio.h"
#include "Paquete.h"
#include "Sobre.h"
#include "Tracking.h"
#include "ColaEnvios.h"
#include "Usuario.h"
#include "Pago.h"
#include <map>

int main() {
    Usuario usuarioActual;
    short opcionAcceso;
    bool estaAutenticado = false;

    while (!estaAutenticado) {
        mostrarMenuAcceso();
        cin >> opcionAcceso;

        if (opcionAcceso == 1) {
            usuarioActual.registrarUsuario();
            cout << "Ahora debe iniciar sesion.\n";
            Sleep(1500);
            system("cls");
        }
        else if (opcionAcceso == 2) {
            string correo, pass;
            cout << "Correo: "; cin >> correo;
            cout << "Password: "; cin >> pass;

            if (!usuarioActual.iniciarSesion(correo, pass)) {
                cout << "Correo o password incorrectos.\n";
            }
            else {
                cout << "Sesion iniciada correctamente.\n";
                estaAutenticado = true;
            }
            Sleep(1500);
            system("cls");
        }
        else {
            cout << "Saliendo del programa...\n";
            Sleep(1500);
            return 0;
        }
    }   

	ListaEnvios lista;
    ColaEnvios cola;
    map<int, Tracking*> trackings;
	short opcion;

    //Caso de prueba paquete
    Envio* p1 = new Paquete(1, 4.0, "20x5x100", "Lima", "Cusco", "Pendiente","Ropa", 200.0, true);
    lista.insertarInicio(p1);
    trackings[p1->getId()] = new Tracking(p1->getId());
    //Caso de prueba sobre
    Envio* s1 = new Sobre(2,0.5,"A4","Arequipa","Lima","Pendiente",25,true,true);
    lista.insertarInicio(s1);
    trackings[p1->getId()] = new Tracking(p1->getId());

    cola.encolar(p1);
    cola.encolar(s1);

    cola.mostrarCola();

    cola.desencolar();

    cola.mostrarCola();

	while (1) {
		system("cls");
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
                cola.encolar(nuevo);
                trackings[idEnvio] = new Tracking(idEnvio);
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
                cola.encolar(nuevo);
                trackings[idEnvio] = new Tracking(idEnvio);
                cout << "Sobre registrado con costo: " << nuevo->getCosto() << " soles\n";
            }
            else {
                cout << "Tipo de envio no válido.\n";
            }
            system("pause>0");
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
            system("pause>0");
        }

        if (opcion == 3) {
            int idEliminar;
            cout << "Ingrese el ID a eliminar: ";
            cin >> idEliminar;
            lista.eliminarPorId(idEliminar);
            system("pause>0");
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
            system("pause>0");
        }

		if (opcion == 5) {
            int id;
            cout << "Ingrese ID del envio: "; cin >> id;

            if (trackings.find(id) != trackings.end()) {
                trackings[id]->mostrarHistorial();
            }
            else {
                cout << "No existe tracking para este envio.\n";
            }
            system("pause>0");
		}

        if (opcion == 6){
            int id;
            string ubicacion;
            cout << "Ingrese ID del envio: "; cin >> id;
            cout << "Ingrese nueva ubicacion: "; cin.ignore(); getline(cin, ubicacion);

            if (trackings.find(id) != trackings.end()) {
                trackings[id]->pushUbicacion(ubicacion);
            }
            else {
                cout << "No existe tracking para el envio con ID " << id << endl;
            }
            system("pause>0");
        }

        if (opcion == 7) {
            int id;
            cout << "Ingrese ID del envio: "; cin >> id;

            if (trackings.find(id) != trackings.end()) {
                cout << "Ultima ubicacion: " << trackings[id]->verUltimaUbicacion() << endl;
            }
            else {
                cout << "No existe tracking para este envio.\n";
            }
            system("pause>0");
        }

        if (opcion == 8) {
            cola.mostrarCola();
            system("pause>0");
        }

        if (opcion == 9) {
            cola.desencolar();
            system("pause>0");
        }

        if (opcion == 10) {
            int idBuscar;
            cout << "Ingrese ID del envio a pagar: ";
            cin >> idBuscar;

            Envio* envioBuscado = lista.buscarEnvioPorId(idBuscar);

            if (envioBuscado != nullptr) {
                string dni, metodo;
                cout << "Ingrese DNI del usuario: ";
                cin >> dni;
                cout << "Monto a pagar: S/." << envioBuscado->getCosto() << "\n";
                cout << "Metodo de pago (Tarjeta/Yape/Plin/Efectivo): ";
                cin >> metodo;

                Pago<double> pago(dni, metodo, envioBuscado);
                pago.registrarPago();
            }
            else {
                cout << "No se encontro el envio con ID " << idBuscar << "\n";
            }
            system("pause>0");
        }

        if (opcion == 11) {
            Pago<double> gestor;
            gestor.mostrarPagos();
            system("pause>0");
        }

        if (opcion == 12) {
            lista.mostrarLista();
            system("pause>0");
        }
	}

    system("pause>0");
    return 0;
}