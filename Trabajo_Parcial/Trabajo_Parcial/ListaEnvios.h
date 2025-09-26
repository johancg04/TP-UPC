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

	void insertar(Envio* e) {
		Nodo* nuevo = new Nodo(e);
		nuevo->setSiguiente(cabeza);
		cabeza = nuevo;
	}

	void mostrar() {
		Nodo* aux = cabeza;
		while (aux) {
			aux->getEnvio()->mostrar();
			aux = aux->getSiguiente();
		}
	}
};