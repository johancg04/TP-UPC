#pragma once
#include "Envio.h"
//NODO PARA ENVIOS
class Nodo
{
private:
    Envio* envio;
    Nodo* siguiente;
public:
    Nodo(Envio* e) {
        envio = e;
        siguiente = nullptr;
    }

    ~Nodo() {}

    Envio* getEnvio() { return envio; }
    void setEnvio(Envio* e) { envio = e; }

    Nodo* getSiguiente() { return siguiente; }
    void setSiguiente(Nodo* nodo) { siguiente = nodo; }
};