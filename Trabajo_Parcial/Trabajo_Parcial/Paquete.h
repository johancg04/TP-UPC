#pragma once
#include "Envio.h"

class Paquete : public Envio
{
private:
	string contenido;
	double volumen;
	double valorDeclarado;
	bool asegurado;
public:
	Paquete(int id, double p, string dim, string ori, string des, string est, string conte, double valor, bool aseg) :Envio(id, "Paquete", p, dim, ori, des, est) {
		this->contenido = conte;
		this->volumen = 1;
		this->valorDeclarado = valor;
		this->asegurado = aseg;
		calcularCosto();
		calcularVolumen();
	}

	~Paquete() {}

	void calcularCosto() override {
		costo = (peso * 5.0) + (valorDeclarado * 0.01);
		if (asegurado) {
			costo += 15.0;
		}
		costo += volumen / 10.0;
	}

	void mostrar() override {
		cout << "Envio " << idEnvio << "\tTipo: {" << tipo << "} \n";
		cout << "Origen: " << origen << "\tDestino: " << destino << "\n";
		cout << "Estado: " << estado << "\tCosto: " << getCosto() << "\n";
		cout << "Volumen: " << volumen << "\tValor declarado: " << valorDeclarado << "\n";
		cout << "Contenido: " << contenido << "\tAsegurado: " << (asegurado ? "Si" : "No") << "\n";
	}

	void calcularVolumen() {
		string temp = "";
		volumen = 1;

		for (int i = 0; i <= dimensiones.length(); i++) {
			if (i < dimensiones.length() && isdigit(dimensiones[i])) {
				temp += dimensiones[i];
			}
			else if (temp != "") {
				volumen *= stoi(temp);
				temp = "";
			}
		}
	}


};