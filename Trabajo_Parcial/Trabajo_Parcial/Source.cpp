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
                cout << "Sesion iniciada correctamente como " << usuarioActual.getRol() << ".\n";
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
    lista.cargarDesdeArchivo();
    ColaEnvios cola;
    map<int, Tracking*> trackings;
    short opcion;

    if (usuarioActual.getRol() == "Cliente") {
        do {
            system("cls");
            mostrarMenuCliente();
            cout << "Ingrese opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
            {
                int idEnvio;
                string tipo, dimensiones, origen, destino, estado;
                double peso;

                cout << "ID Envio: "; cin >> idEnvio;
                cout << "Tipo de envio (Paquete/Sobre): "; cin >> tipo;
                cout << "Peso: "; cin >> peso;
                cout << "Dimensiones: "; cin >> dimensiones;
                cout << "Origen: "; cin >> origen;
                cout << "Destino: "; cin >> destino;
                estado = "Pendiente";
                Envio* nuevo = nullptr;
                if (tipo == "Paquete") {
                    string contenido;
                    double valorDeclarado;
                    bool asegurado;

                    cout << "Contenido: "; cin >> contenido;
                    cout << "Valor declarado: "; cin >> valorDeclarado;
                    cout << "Asegurado? (1=Si, 0=No): "; cin >> asegurado;

                    nuevo = new Paquete(idEnvio, peso, dimensiones, origen, destino, estado,
                        contenido, valorDeclarado, asegurado, usuarioActual.getDni());
                }
                else if (tipo == "Sobre") {
                    int numeroHojas;
                    bool urgente;
                    bool clienteFrecuente;

                    cout << "Número de hojas: "; cin >> numeroHojas;
                    cout << "Es urgente? (1=Si, 0=No): "; cin >> urgente;
                    cout << "Cliente frecuente? (1=Si, 0=No): "; cin >> clienteFrecuente;

                    nuevo = new Sobre(idEnvio, peso, dimensiones, origen, destino, estado,
                        numeroHojas, urgente, clienteFrecuente, usuarioActual.getDni());
                }
                if (nuevo != nullptr) {
                    lista.insertarInicio(nuevo);
                    cola.encolar(nuevo);
                    trackings[idEnvio] = new Tracking(idEnvio);

                    cout << "Envio registrado con costo: " << nuevo->getCosto() << " soles\n";
                }
                else {
                    cout << "Tipo de envio no valido.\n";
                }
                system("pause>0");
                break;
            }
            case 2:
            {
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
                break;
            }
            case 3:
            {
                int id;
                cout << "Ingrese ID del envio: "; cin >> id;

                if (trackings.find(id) != trackings.end()) {
                    trackings[id]->mostrarHistorial();
                }
                else {
                    cout << "No existe tracking para este envio.\n";
                }
                system("pause>0");
                break;
            }
            case 4:
            {
                int id;
                cout << "Ingrese ID del envio: "; cin >> id;

                if (trackings.find(id) != trackings.end()) {
                    cout << "Ultima ubicacion: " << trackings[id]->verUltimaUbicacion() << endl;
                }
                else {
                    cout << "No existe tracking para este envio.\n";
                }
                system("pause>0");
                break;
            }
            case 5:
            {
                int idBuscar;
                cout << "Ingrese ID del envio a pagar: ";
                cin >> idBuscar;

                Envio* envioBuscado = lista.buscarEnvioPorId(idBuscar);

                if (envioBuscado != nullptr) {
                    string metodo;
                    cout << "Monto a pagar: S/." << envioBuscado->getCosto() << "\n";
                    cout << "Metodo de pago (Tarjeta/Yape/Plin/Efectivo): ";
                    cin >> metodo;

                    Pago<double> pago(usuarioActual.getDni(), metodo, envioBuscado);
                    pago.registrarPago();
                }
                else {
                    cout << "No se encontro el envio con ID " << idBuscar << "\n";
                }
                system("pause>0");
                break;
            }
            case 6:
            {
                Pago<double> gestor;
                gestor.mostrarPagos(usuarioActual.getDni());
                system("pause>0");
                break;
            }
            case 7:
            {
                lista.mostrarPorDni(usuarioActual.getDni());
                system("pause>0");
                break;
            }
            }
        } while (opcion != 0);
    }

    if (usuarioActual.getRol() == "Administrador") {
        do {
            system("cls");
            mostrarMenuAdmin();
            cout << "Ingrese opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
            {
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
                break;
            }
            case 2:
            {
                int idEliminar;
                cout << "Ingrese el ID a eliminar: ";
                cin >> idEliminar;
                lista.eliminarPorId(idEliminar);
                system("pause>0");
                break;
            }
            case 3:
            {
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
                break;
            }
            case 4:
            {
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
                break;
            }
            case 5:
            {
                int id;
                cout << "Ingrese ID del envio: "; cin >> id;

                if (trackings.find(id) != trackings.end()) {
                    trackings[id]->mostrarHistorial();
                }
                else {
                    cout << "No existe tracking para este envio.\n";
                }
                system("pause>0");
                break;
            }
            case 6:
            {
                int id;
                cout << "Ingrese ID del envio: "; cin >> id;

                if (trackings.find(id) != trackings.end()) {
                    cout << "Ultima ubicacion: " << trackings[id]->verUltimaUbicacion() << endl;
                }
                else {
                    cout << "No existe tracking para este envio.\n";
                }
                system("pause>0");
                break;
            }
            case 7:
            {
                cola.mostrarCola();
                system("pause>0");
                break;
            }
            case 8:
            {
                cola.desencolar();
                system("pause>0");
                break;
            }
            case 9:
            {
                Pago<double> gestor;
                gestor.mostrarPagos();
                system("pause>0");
                break;
            }
            case 10:
            {
                lista.mostrarLista();
                system("pause>0");
                break;
            }
            }
        } while (opcion != 0);
    }
    system("pause>0");
    return 0;
}