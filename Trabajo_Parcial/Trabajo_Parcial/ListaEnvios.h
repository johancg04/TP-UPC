#pragma once
#include "Nodo.h"
#include "Headers.h"
#include "Paquete.h"
#include "Sobre.h"

template <typename T>
class ListaEnvios
{
private:
	Nodo<T>* cabeza;

public:
	ListaEnvios() {
		cabeza = nullptr;
	}
	~ListaEnvios(){}

	void insertarInicio(T* e) {
		Nodo<T>* nuevo = new Nodo<T>(e);
		nuevo->setSiguiente(cabeza);
		cabeza = nuevo;

        guardarEnArchivo(e);
	}

    void mostrarListaRecursivo(Nodo<T>* temp) {
        if (temp == nullptr) {
            return;
        }
        T* e = temp->getEnvio();
        if (e != nullptr) {
            e->mostrar();
        }
        if (temp->getSiguiente() != nullptr) {
            cout << "-----------------------------------\n";
        }
        mostrarListaRecursivo(temp->getSiguiente());
    }

    void mostrarLista() {
        cout << endl << "=== LISTA DE ENVIOS ===" << endl;
        mostrarListaRecursivo(cabeza);
    }

    T* buscarEnvioPorIdRecursivo(Nodo<T>* nodo, int id) {
        if (nodo == nullptr) {
            return nullptr;
        }
        if (nodo->getEnvio()->getId() == id) {
            return nodo->getEnvio();
        }
        return buscarEnvioPorIdRecursivo(nodo->getSiguiente(), id);
    }

    T* buscarEnvioPorId(int id) {
        return buscarEnvioPorIdRecursivo(cabeza, id);
    }

    Nodo<T>* eliminarPorIdRecursivoInterno(Nodo<T>* nodo, int id, bool& eliminado) {
        if (nodo == nullptr) {
            return nullptr;
        }

        if (nodo->getEnvio()->getId() == id) {
            Nodo<T>* siguiente = nodo->getSiguiente();
            delete nodo->getEnvio();
            delete nodo;
            eliminado = true;
            return siguiente;
        }

        nodo->setSiguiente(eliminarPorIdRecursivoInterno(nodo->getSiguiente(), id, eliminado));
        return nodo;
    }

    void eliminarPorId(int id) {
        bool eliminado = false;
        cabeza = eliminarPorIdRecursivoInterno(cabeza, id, eliminado);

        if (eliminado) {
            cout << "Envio con ID " << id << " eliminado.\n";
            reescribirArchivo();
        }
        else {
            cout << "Envio con ID " << id << " no encontrado.\n";
        }
    }

    void mostrarPorDni(const string& dni) {
        auto coincideDni = [dni](T* e) {
            return e && e->getDniCliente() == dni;
            };

        Nodo<T>* temp = cabeza;
        bool encontrado = false;
        cout << "\n=== ENVIOS DEL DNI: " << dni << " ===\n";
        while (temp) {
            T* e = temp->getEnvio();
            if (coincideDni(e)) {
                e->mostrar();
                cout << "-----------------------------------\n";
                encontrado = true;
            }
            temp = temp->getSiguiente();
        }
        if (!encontrado)
            cout << "No se encontraron envíos para el DNI " << dni << "\n";
    }

    void guardarEnArchivo(T* e) {
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
                T* nuevo = nullptr;

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

    void filtrarEnviosPorCriterio(const string& valorFiltro) {
        cout << "\n=== FILTRO DE ENVIOS POR CRITERIO ===\n";

        auto cumpleCriterio = [valorFiltro](Envio* e) {
            return (e->getOrigen() == valorFiltro || e->getDestino() == valorFiltro);
            };

        Nodo<T>* temp = cabeza;
        bool encontrado = false;

        while (temp) {
            T* e = temp->getEnvio();
            if (e && cumpleCriterio(e)) {
                e->mostrar();
                cout << "-----------------------------------\n";
                encontrado = true;
            }
            temp = temp->getSiguiente();
        }

        if (!encontrado)
            cout << "No se encontraron envios que coincidan con el criterio: " << valorFiltro << "\n";
    }

    private:

        void insertarInicioSinArchivo(T* e) {
            Nodo<T>* nuevo = new Nodo<T>(e);
            nuevo->setSiguiente(cabeza);
            cabeza = nuevo;
        }

        void reescribirArchivo() {
            ofstream archivo("envios.txt", ios::trunc);
            if (!archivo.is_open()) {
                cout << "Error al abrir archivo de envíos.\n";
                return;
            }

            Nodo<T>* temp = cabeza;
            while (temp) {
                T* e = temp->getEnvio();
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