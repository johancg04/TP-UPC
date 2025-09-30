#pragma once
#include "Envio.h"
#include <fstream>

template <typename T>
class Pago
{
private:
	string dniUsuario;
	string metodo;
	T monto;
	int idEnvio;
public:
	Pago() {
		this->dniUsuario = "";
		this->metodo = "";
		this->monto = 0;
		this->idEnvio = 0;
	}

	Pago(string dni, string metodo, Envio* envio) {
		this->dniUsuario = dni;
		this->metodo = metodo;
		this->monto = envio->getCosto();
		this->idEnvio = envio->getId();
	}

	~Pago(){}

	void registrarPago() {
		ofstream archivo("pagos.txt", ios::app);
		archivo << "---------PAGO---------\n";
		archivo << "DNI:" << dniUsuario << "\n";
		archivo << "EnvioID:" << idEnvio << "\n";
		archivo << "Metodo:" << metodo << "\n";
		archivo << "Monto:" << monto << "\n";
		archivo << "----------------------\n";
		archivo.close();

		cout << "Pago registrado correctamente\n";
	}

	void mostrarPagos() {
		ifstream archivo("pagos.txt");
		string linea;
		cout << "\n===== LISTA DE PAGOS =====\n";
		while (getline(archivo, linea)) {
			cout << linea << endl;
		}
		archivo.close();
	}
};