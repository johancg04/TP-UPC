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
	Envio() {}

    Envio(int id, string t, double p, string dim, string o, string d, string e) {
		this->idEnvio = id;
		this->tipo = t;
		this->peso = p;
		this->dimensiones = dim;
		this->origen = o;
		this->destino = d;
		this->estado = e;
		calcularCosto();
	}

	~Envio(){}

	void mostrar() {
		cout << "Envio " << idEnvio << "\tTipo: {" << tipo << "} \n";
		cout << "Origen: " << origen << "\tDestino: " << destino << "\n";
		cout << "Estado: " << estado << "\tCosto: " << getCosto();
	}

	void registrarEnvio() {
		cout << "Se registro el envio [" << idEnvio << "] hacia " << destino << " (" << tipo << ")\n";
	}

	void calcularCosto() {
		string t = tipo;
		if (t == "Paquete") {
			costo = peso * 5.0;
		}
		else if (t == "Sobre") {
			costo = peso * 2.0;
		}
		else {
			costo = peso * 3.0;
		}
	}

	void actualizarEstado(string nuevoEstado) {
		estado = nuevoEstado;
		cout << "Estado del envio [" << idEnvio << "] actualizado a: " << estado << endl;
	}


	int getId() { return idEnvio; }
	string getTipo() { return tipo; }
	double getPeso() { return peso; }
	string getDimensiones() { return dimensiones; }
	string getOrigen() { return origen; }
	string getDestino() { return destino; }
	double getCosto() { return costo; }
	string getEstado() { return estado; }

	void setEstado(string nuevoEstado) { estado = nuevoEstado; }
	void setCosto(double nuevoCosto) { costo = nuevoCosto; }
	void setId(int id) { idEnvio = id; }
	void setTipo(string t) { tipo = t; }
	void setPeso(double p) { peso = p; }
	void setDimensiones(string d) { dimensiones = d; }
	void setOrigen(string o) { origen = o; }
	void setDestino(string d) { destino = d; }
};