#pragma once
#include "Envio.h"

class Sobre: public Envio
{
private:
	int numeroHojas;
	bool urgencia;
	bool clienteFrecuente;
public:
	Sobre(int id, double p, string dim, string ori, string des, string est, int hojas, bool urg, bool frec, string dni):Envio(id, "Sobre",p,dim,ori,des,est, dni) {
		this->numeroHojas = hojas;
		this->urgencia = urg;
		this->clienteFrecuente = frec;
		calcularCosto();
	}
	~Sobre(){}

	int getNumeroHojas() { return numeroHojas; }
	bool getUrgente() { return urgencia; }
	bool getClienteFrecuente() { return clienteFrecuente; }

	void calcularCosto() override {
		costo = peso * 2.0;
		if (urgencia) costo += 10.0;
		costo += (numeroHojas / 10) * 1.0;

		if (clienteFrecuente) {
			costo -= costo * 0.10;
		}
	}

	void mostrar() override {
		cout << "Envio " << idEnvio << "\tTipo: {" << tipo << "} \n";
		cout << "Origen: " << origen << "\tDestino: " << destino << "\n";
		cout << "Estado: " << estado << "\tCosto: " << getCosto() << "\n";
		cout << "N" << char(167) <<  " hojas: " << numeroHojas << "\tUrgente : " << (urgencia ? "Si" : "No") << "\n";
	}

};