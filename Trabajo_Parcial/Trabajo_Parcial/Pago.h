#pragma once
#include "Envio.h"
#include "Headers.h"

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

	void mostrarPagos(const string& dniFiltro = "") {
		ifstream archivo("pagos.txt");
		if (!archivo.is_open()) {
			cout << "Error al abrir pagos.txt\n";
			return;
		}

		string linea;
		string dniArchivo, metodoArchivo, montoArchivo, idArchivo;

		cout << "\n===== LISTA DE PAGOS =====\n";
		while (getline(archivo, linea)) {
			if (linea.rfind("DNI:", 0) == 0) {
				dniArchivo = linea.substr(4);
			}
			else if(linea.rfind("ID:", 0) == 0) {
				idArchivo = linea.substr(3);
			}
			else if (linea.rfind("Metodo:", 0) == 0) {
				metodoArchivo = linea.substr(7);
			}
			else if (linea.rfind("Monto:", 0) == 0) {
				montoArchivo = linea.substr(6);

				// Aquí se aplica el filtro:
				if (dniFiltro == "" || dniArchivo == dniFiltro) {
					cout << "DNI: " << dniArchivo << "\n";
					cout << "Metodo: " << metodoArchivo << "\n";
					cout << "Monto: " << montoArchivo << "\n";
					cout << "-------------------\n";
				}

				dniArchivo = "";
				metodoArchivo = "";
				montoArchivo = "";
			}
		}
		archivo.close();
	}

};