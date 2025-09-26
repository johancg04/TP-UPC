#pragma once
#include "Headers.h"

class Envio
{
private:
	int idEnvio = 0;
	string tipo = "";
	double peso = 0.0;
	string dimensiones = "";
	string origen = "";
	string destino = "";
	double costo = 0.0;
	string estado = "";

public:
	Envio() {

	}

    Envio(int id, string t, double p, string dim, string o, string d, double c, string e) {
		this->idEnvio = id;
		this->tipo = t;
		this->peso = p;
		this->dimensiones = dim;
		this->origen = o;
		this->destino = d;
		this->costo = c;
		this->estado = e;
	}

	~Envio(){}

	void mostrar() {
		cout << "Envio " << idEnvio << "\tTipo: {" << tipo << "} \n";
		cout << "Destino: " << destino << "\tEstado: " << estado << "\n";
		cout << "Costo: " << costo << "\n";
	}

	void registrarEnvio() {
		cout << "ID Envio: "; cin >> idEnvio;
		cout << "Tipo de envio: "; cin >> tipo;
		cout << "Peso: "; cin >> peso;
		cout << "Dimensiones: "; cin >> dimensiones;
		cout << "Origen: "; cin >> origen;
		cout << "Destino: "; cin >> destino;
		cout << "Costo: "; cin >> costo;
		cout << "Estado: "; cin >> estado;
	}

	string getDestino() { return destino; }

	double getCosto() { return costo; }

	int getId() { return idEnvio; }
};