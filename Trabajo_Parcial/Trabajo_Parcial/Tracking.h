#pragma once
#include "Headers.h"

template <typename T>
class Tracking
{
private:
	int idEnvio;
	stack<T> ubicaciones;
public:
	Tracking(int id) {
		this->idEnvio = id;
	}

	~Tracking(){}

	void pushUbicacion(const T& ubicacion) {
		ubicaciones.push(ubicacion);
	}

	void popUbicacion() {
		if (!ubicaciones.empty()) {
			cout << "Eliminando ultima ubicacion: " << ubicaciones.top() << "\n";
			ubicaciones.pop();
		}
		else {
			cout << "No hay ubicaciones en el historial\n";
		}
	}

	T verUltimaUbicacion() {
		if (!ubicaciones.empty()) {
			return ubicaciones.top();
		}
		cout << "No hay ubicaciones registradas\n";
		return T();
	}

	void mostrarHistorial() {
		if (ubicaciones.empty()) {
			cout << "No hay historial de ubicaciones.\n";
			return;
		}
		cout << "Historial de ubicaciones del envio " << idEnvio << ":\n";

		stack<T> copia = ubicaciones;

		auto imprimirPila = [](stack<T> s) {
			while (!s.empty()) {
				cout << "- " << s.top() << endl;
				s.pop();
			}
		};

		imprimirPila(copia);
	}
};