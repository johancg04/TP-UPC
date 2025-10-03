#pragma once
#include "Nodo.h"
#include "Headers.h"
#include "Paquete.h"
#include "Sobre.h"

class ListaEnvios
{
private:
	Nodo* cabeza;

public:
	ListaEnvios() {
		cabeza = nullptr;
	}
	~ListaEnvios(){}

	void insertarInicio(Envio* e) {
		Nodo* nuevo = new Nodo(e);
		nuevo->setSiguiente(cabeza);
		cabeza = nuevo;

        guardarEnArchivo(e);
	}

    void mostrarLista() {
        if (cabeza == nullptr) {
            cout << endl << "LISTA DE ENVIOS VACIA\n" << endl;
            return;
        }

        Nodo* temp = cabeza;
        cout << endl << "=== LISTA DE ENVIOS ===" << endl;

        while (temp != nullptr) {
            Envio* e = temp->getEnvio();
            if (e != nullptr) {
                e->mostrar();
            }
            if (temp->getSiguiente() != nullptr) {
                cout << "-----------------------------------\n";
            }
            temp = temp->getSiguiente();
        }
        cout << endl;
    }

    Envio* buscarEnvioPorId(int id) {
        Nodo* temp = cabeza;
        while (temp != nullptr) {
            Envio* e = temp->getEnvio();
            if (e!= nullptr && e->getId() == id) {
                return temp->getEnvio();
            }
            else {
                temp = temp->getSiguiente();
            }
         }
        return nullptr;
    }

    void eliminarPorId(int id) {
        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        while (actual != nullptr) {
            Envio* e = actual->getEnvio();
            if (e->getId() == id) {
                if (anterior == nullptr) {
                    cabeza = actual->getSiguiente();
                }
                else {
                    anterior->setSiguiente(actual->getSiguiente());
                }
                delete e;
                delete actual;
                cout << "Envio con ID " << id << " eliminado.\n";
                // Reescribir archivo sin ese envío
                reescribirArchivo();
                return;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        cout << "Envio con ID " << id << " no encontrado.\n";
    }

    void mostrarPorDni(const string& dni) {
        Nodo* temp = cabeza;
        bool found = false;
        cout << "\n=== ENVIOS DEL DNI: " << dni << " ===\n";
        while (temp) {
            Envio* e = temp->getEnvio();
            if (e && e->getDniCliente() == dni) {
                e->mostrar();
                cout << "-----------------------------------\n";
                found = true;
            }
            temp = temp->getSiguiente();
        }
        if (!found) cout << "No se encontraron envíos para el DNI " << dni << "\n";
    }

    void guardarEnArchivo(Envio* e) {
        ofstream archivo("envios.txt", ios::app);
        if (!archivo.is_open()) {
            cout << "Error al abrir archivo de envios\n";
            return;
        }

        archivo << "ID:" << e->getId() << "\n";
        archivo << "Tipo:" << e->getTipo() << "\n";
        archivo << "Peso:" << e->getPeso() << "\n";
        archivo << "Dimensiones:" << e->getDimensiones() << "\n";
        archivo << "Origen:" << e->getOrigen() << "\n";
        archivo << "Destino:" << e->getDestino() << "\n";
        archivo << "Estado:" << e->getEstado() << "\n";
        archivo << "DNI:" << e->getDniCliente() << "\n";

        if (e->getTipo() == "Paquete") {
            Paquete* p = dynamic_cast<Paquete*>(e); // convirtiendo a una clase base
            archivo << "Contenido:" << p->getContenido() << "\n";
            archivo << "Valor:" << p->getValorDeclarado() << "\n";
            archivo << "Asegurado:" << (p->getAsegurado() ? 1 : 0) << "\n";
        }

        if (e->getTipo() == "Sobre") {
			Sobre* s = dynamic_cast<Sobre*>(e); // convirtiendo a una clase base
            archivo << "Hojas:" << s->getNumeroHojas() << "\n";
            archivo << "Urgente:" << (s->getUrgente() ? 1 : 0) << "\n";
            archivo << "Frecuente:" << (s->getClienteFrecuente() ? 1 : 0) << "\n";
        }

        archivo << "-------------------\n";
        archivo.close();
    }

    void cargarDesdeArchivo() {
        ifstream archivo("envios.txt");
        if (!archivo.is_open()) return;

        string linea;
        int id; string tipo, dim, ori, des, est, dni;
        double peso;
        string contenido; double valor; bool aseg;
        int hojas; bool urg; bool frec;


        while (getline(archivo, linea)) {
            if (linea.rfind("ID:", 0) == 0) {
                id = stoi(linea.substr(3));
            }
            else if (linea.rfind("Tipo:", 0) == 0) {
                tipo = linea.substr(5);
            }
            else if (linea.rfind("Peso:", 0) == 0) {
                peso = stod(linea.substr(5));
            }
            else if (linea.rfind("Dimensiones:", 0) == 0) {
                dim = linea.substr(12);
            }
            else if (linea.rfind("Origen:", 0) == 0) {
                ori = linea.substr(7);
            }
            else if (linea.rfind("Destino:", 0) == 0) {
                des = linea.substr(8);
            }
            else if (linea.rfind("Estado:", 0) == 0) {
                est = linea.substr(7);
            }
            else if (linea.rfind("DNI:", 0) == 0) {
                dni = linea.substr(4);
            }
            else if (linea.rfind("Contenido:",0) == 0) {
				contenido = linea.substr(10);
            }
            else if(linea.rfind("Valor:", 0) == 0) {
                valor = stod(linea.substr(6));
            }
            else if (linea.rfind("Asegurado:", 0) == 0) {
                aseg = stoi(linea.substr(10));
            }
            else if (linea.rfind("Hojas:", 0) == 0) {
                hojas = stoi(linea.substr(6));
            }
            else if (linea.rfind("Urgente:", 0) == 0) {
                urg = stoi(linea.substr(8));
            }
            else if (linea.rfind("Frecuente:", 0) == 0) {
                frec = stoi(linea.substr(10));
			}   

            else if (linea == "-------------------") {
                Envio* nuevo = nullptr;

                if (tipo == "Paquete") {
                    nuevo = new Paquete(id, peso, dim, ori, des, est, contenido, valor, aseg, dni);
                }
                else if (tipo == "Sobre") {
                    nuevo = new Sobre(id, peso, dim, ori, des, est, hojas, urg, frec, dni);
                }
                if (nuevo != nullptr) {
                    insertarInicioSinArchivo(nuevo);
                }
            }
        }

        archivo.close();
    }

    private:
        void insertarInicioSinArchivo(Envio* e) {
            Nodo* nuevo = new Nodo(e);
            nuevo->setSiguiente(cabeza);
            cabeza = nuevo;
        }
        // POR PROBAR
        void reescribirArchivo() {
            ofstream archivo("envios.txt", ios::trunc);
            if (!archivo.is_open()) {
                cout << "Error al abrir archivo de envíos.\n";
                return;
            }

            Nodo* temp = cabeza;
            while (temp) {
                Envio* e = temp->getEnvio();
                archivo << "ID:" << e->getId() << "\n";
                archivo << "Tipo:" << e->getTipo() << "\n";
                archivo << "Peso:" << e->getPeso() << "\n";
                archivo << "Dimensiones:" << e->getDimensiones() << "\n";
                archivo << "Origen:" << e->getOrigen() << "\n";
                archivo << "Destino:" << e->getDestino() << "\n";
                archivo << "Estado:" << e->getEstado() << "\n";
                archivo << "DNI:" << e->getDniCliente() << "\n";

                if (e->getTipo() == "Paquete") {
                    Paquete* p = dynamic_cast<Paquete*>(e);
                    archivo << "Contenido:" << p->getContenido() << "\n";
                    archivo << "Valor:" << p->getValorDeclarado() << "\n";
                    archivo << "Asegurado:" << (p->getAsegurado() ? 1 : 0) << "\n";
                }

                if (e->getTipo() == "Sobre") {
                    Sobre* s = dynamic_cast<Sobre*>(e);
                    archivo << "Hojas:" << s->getNumeroHojas() << "\n";
                    archivo << "Urgente:" << (s->getUrgente() ? 1 : 0) << "\n";
                    archivo << "Frecuente:" << (s->getClienteFrecuente() ? 1 : 0) << "\n";
                }

                archivo << "-------------------\n";
                temp = temp->getSiguiente();
            }
            archivo.close();
        }

};