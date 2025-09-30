#pragma once
#include "Headers.h"
#include <stack>

class Tracking
{
private:
	int idEnvio;
	stack<string> ubicaciones;
public:
	Tracking(int id) {
		this->idEnvio = id;
	}

	~Tracking(){}

	void pushUbicacion(const string& ubicacion) {
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

	string verUltimaUbicacion() {
		if (!ubicaciones.empty()) {
			return ubicaciones.top();
		}
		return "No hay ubicaciones registradas";
	}

	void mostrarHistorial() {
		if (ubicaciones.empty()) {
			cout << "No hay historial de ubicaciones.\n";
			return;
		}
		cout << "Historial de ubicaciones del envio " << idEnvio << ":\n";

		stack<string> copia = ubicaciones;
		while (!copia.empty()) {
			cout << "- " << copia.top() << endl;
			copia.pop();
		}
	}
};