#pragma once
#include "Nodo.h"

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
                if (anterior == nullptr) { //si elimino el primer nodo
                    cabeza = actual->getSiguiente();
                }
                else {
                    anterior->setSiguiente(actual->getSiguiente());
                }
                delete e;
                delete actual;
                cout << "Envio con ID " << id << " eliminado.\n";
                return;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        cout << "Envio con ID " << id << " no encontrado.\n";
    }
};